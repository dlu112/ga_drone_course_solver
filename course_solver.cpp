#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "common.h"
#include "GeneticAlgorithm.h"

using namespace std;

// Calculates the cost of visiting ALL waypoints in a course
double calculateInitialCost(size_t n, vector<Waypoint> waypoints) {
    Coord current = START_COORD;
    double cost = 0.0;

    for (int i = 0; i < n; i++) {
        Coord new_coord = { waypoints[i].x, waypoints[i].y };
        cost += calculateTravelCost(current.x, current.y, new_coord.x, new_coord.y);
        current = new_coord;
    }

    cost += calculateTravelCost(current.x, current.y, END_COORD.x, END_COORD.y);
    return cost;
}

// Run genetic algorithm
void courseSolver(vector<Waypoint> waypoints) {
    auto n = waypoints.size();

    // calculate the initial cost of visiting all waypoints in order
    // double initial_cost = calculateInitialCost(n, waypoints);
    // printf("Initial cost: %.3f\n", initial_cost);

    // run genetic algorithm to solve for optimal solution
    GeneticAlgorithm GASolver(int(n), waypoints);
    double GA_cost = GASolver.solveCourse();

    // print final cost
    printf("%.3f\n", GA_cost);
}

int main(int argc, char *argv[]) {
    // accept a filename as the argument and begin reading from it
    string file_name = argv[1];
    ifstream input_file(file_name);
    int n = -1;

    for (string line; getline(input_file, line);) {

        // check if file has ended and break
        if (line == "0") break;

        // check if we've started a new test case
        if (n == -1) {
            // the next n input lines will be the waypoints for the new test case
            n = stoi(line);
        }
        else {
            // parse the current line and add to waypoint values
            int val;
            vector<int> input_ints;
            stringstream ssline(line);
            while ((ssline >> val)) input_ints.push_back(val);
            Waypoint new_waypoint = { input_ints[0], input_ints[1], input_ints[2] };
            waypoints.push_back(new_waypoint);
            n -= 1;
        }

        // solve when all waypoints have been generated
        if (n == 0) {
            courseSolver(waypoints);
            // clear the vector and prepare for new test case
            waypoints.clear();
            n -= 1;
        }
    }
}