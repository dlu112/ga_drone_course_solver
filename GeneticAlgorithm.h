#pragma once
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "common.h"

/*
GA overview
1. generate a population
2. evaluate fitness of each member in the pop
3. sort pop to find the fittest members
4. create the next generation
4a. select parents for the next generation
4b. perform crossover
4c. perform mutation
5. repeat step 2-4 until a stopping condition is reached
*/

// An individual member solution in a population
class GAMember {
public:
	GAMember();
	GAMember(std::vector<bool> path);
	GAMember(int member_size);
	double calculateFitness();
	bool operator > (const GAMember& rhs);
	bool operator < (const GAMember& rhs);

	double m_fitness;
	std::vector<bool> m_path;
};

// Runner class for GA
class GeneticAlgorithm {
private:
	// tunable parameters
	int pop_size = 1000;
	int max_generations = 1000;
	double mutation_rate = 0.6;
	double p_mutation = 0.6;
	double p_crossover = 0.6;
	double p_elite = 0.0;
	int plateau_cap = 20;
	double decay = 1.0;

	// internal parameters
	int cur_gen = 0;
	std::vector<GAMember> population;
	bool logger = false;
	bool debug = false;

	// internal functions
	void createInitialPopulation();
	void sortPopulationFitness();
	GAMember crossover(GAMember* p1, GAMember* p2);
	void mutate(std::vector<bool> child);
	void createNewGeneration();
	double getBestCost();

public:
	GeneticAlgorithm();
	GeneticAlgorithm(int m_size, std::vector<Waypoint>& n_waypoints);
	double solveCourse();
	void hyperParameterTuning(double mr, double pm, double pc, double pe, int p_cap, double d_rate);

	// visible parameters
	int member_size;
};
