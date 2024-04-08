#include "GeneticAlgorithm.h"

// Create the initial random population for GA
void GeneticAlgorithm::createInitialPopulation() {
	for (int i = 0; i < pop_size; i++) {
		population.push_back(GAMember(member_size));
	}
}

// Sort all members in a population in ascending order of cost
void GeneticAlgorithm::sortPopulationFitness() {
	std::sort(population.begin(), population.end());
}

// Perform crossover of two parents
GAMember GeneticAlgorithm::crossover(GAMember* p1, GAMember* p2) {
	std::vector<bool> child_path;
	child_path.reserve(member_size);

	// splice together the parents
	int crossover_index = rand() % (member_size + 1);
	child_path.insert(child_path.begin(), p1->m_path.begin(), p1->m_path.begin() + crossover_index);
	child_path.insert(child_path.end(), p2->m_path.begin() + crossover_index, p2->m_path.end());

	// check for mutation
	if (rand() < p_mutation) {
		mutate(child_path);
	}

	return GAMember(child_path);
}

// Perform mutation on a member
void GeneticAlgorithm::mutate(std::vector<bool> child) {
	int n_mutants = int(floor(mutation_rate * member_size));

	for (int i = 0; i < n_mutants; i++) {
		int index = randInt(0, member_size - 1);
		child[index] = !child[index];
	}
}

// Create a new generation from an existing population
void GeneticAlgorithm::createNewGeneration() {
	std::vector<GAMember> new_gen;
	new_gen.reserve(pop_size);

	sortPopulationFitness();

	int n_elite = (int)std::floor(pop_size * p_elite);

	// push elite parents to new gen
	for (int i = 0; i < n_elite; i++) {
		new_gen.push_back(population[i]);
	}

	// perform crossover and mutation
	for (int i = 0; i < (pop_size - n_elite); i++) {
		// get crossover parents
		int p1 = randInt(0, (int)std::floor(pop_size * p_crossover));
		int p2 = randInt(0, (int)std::floor(pop_size * p_crossover));
		new_gen.push_back(crossover(&population[p1], &population[p2]));
	}

	population.clear();
	population = new_gen;
	cur_gen += 1;
}

// Get the best cost in a population
double GeneticAlgorithm::getBestCost() {
	GAMember* best = &population.front();
	return best->calculateFitness();
}

// Default constructor, not used
GeneticAlgorithm::GeneticAlgorithm() {
	member_size = 0;
	population.reserve(pop_size);
}

// Initialization constructor
GeneticAlgorithm::GeneticAlgorithm(int m_size, std::vector<Waypoint>& n_waypoints) {
	member_size = m_size;
	waypoints = n_waypoints;

	// scale population size for smaller cases to improve performance
	if (member_size < 100) pop_size = 1000;
	else if (member_size < 300) pop_size = 3000;
	else if (member_size < 500) pop_size = 6000;
	else pop_size = 10000;

	population.reserve(pop_size);
	createInitialPopulation();
}

// Solve a test case
double GeneticAlgorithm::solveCourse() {
	// logfile for tuning
	std::ofstream logfile;
	std::string logfilename =
		"log-" + std::to_string(p_mutation) +
		"-" + std::to_string(p_crossover) +
		"-" + std::to_string(p_elite) +
		"-" + std::to_string(plateau_cap) +
		".txt";
	if (logger)	logfile.open(logfilename);

	// variables for plateau checking
	double cur_best = 0;
	double best_cost_so_far = -1;
	double cur_best_count = 0;

	if (debug) printf("CURRENT HYPERPARAMS: %f, %f, %f, %i\n", p_mutation, p_crossover, p_elite, plateau_cap);

	// main execution loop
	while (cur_gen < max_generations && cur_best_count < plateau_cap) {
		if (debug) printf("Current generation: %i\n", cur_gen);
		createNewGeneration();

		// check for plateau
		if (best_cost_so_far < 0) best_cost_so_far = getBestCost();
		cur_best = getBestCost();

		// handle plateau
		if (cur_best == best_cost_so_far) {
			cur_best_count += 1;
		}
		else if (cur_best < best_cost_so_far) {
			best_cost_so_far = cur_best;
			cur_best_count == 0;
		}

		if (logger) logfile << best_cost_so_far << "\n";

		// decay p_mutation and p_crossover
		p_mutation = p_mutation * decay;
		p_crossover = p_crossover * decay;
	}

	if (logger) logfile.close();

	double best_cost = getBestCost();

	if (debug) {
		printf("FINAL COST: %.3f\n", best_cost);
		printf("TOTAL ITERATIONS: %i\n", cur_gen);
	}

	// reset internal parameters
	cur_gen = 0;
	population.clear();

	return best_cost;
}

// Modify tunable hyperparameters
void GeneticAlgorithm::hyperParameterTuning(double mr, double pm, double pc, double pe, int p_cap, double d_rate) {
	mutation_rate = mr;
	p_mutation = pm;
	p_crossover = pc;
	p_elite = pe;
	plateau_cap = p_cap;
	decay = d_rate;
}

// Default constructor, not used
GAMember::GAMember() {
	m_fitness = 0;
}

// Construct a new member using an existing one
GAMember::GAMember(std::vector<bool> path) {
	m_path = path;
	m_fitness = calculateFitness();
}

// Construct a new member from scratch
GAMember::GAMember(int member_size) {
	m_path.reserve(member_size);
	for (int i = 0; i < member_size; i++) {
		m_path.push_back(std::rand() % 2);
	}
	m_fitness = calculateFitness();
}

// Calculate the cost of a member using the course waypoints
double GAMember::calculateFitness() {
	Coord current = START_COORD;
	double cost = 0.0;
	for (int i = 0; i < m_path.size(); i++) {
		if (m_path[i]) {
			Coord next_coord = { waypoints[i].x, waypoints[i].y };
			cost += calculateTravelCost(current.x, current.y, next_coord.x, next_coord.y);
			current = next_coord;
		}
		else {
			cost += waypoints[i].penalty;
		}
	}
	cost += calculateTravelCost(current.x, current.y, END_COORD.x, END_COORD.y);
	return cost;
}

// Helper function for sorting a population
bool GAMember::operator > (const GAMember& rhs) {
	return (m_fitness > rhs.m_fitness);
}

// Helper function for sorting a population
bool GAMember::operator < (const GAMember& rhs) {
	return (m_fitness < rhs.m_fitness);
}
