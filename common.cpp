#include "common.h"

// Common global variables
double SPEED = 2.0;
double WAIT_TIME = 10.0;
Coord START_COORD = { 0,0 };
Coord END_COORD = { 100,100 };
std::vector<Waypoint> waypoints;

// Euclidean distance
double calculateDistance(int x1, int y1, int x2, int y2) {
    int x = x1 - x2;
    int y = y1 - y2;
    double dist = pow(x, 2) + pow(y, 2);
    dist = sqrt(dist);
    return dist;
}

// Factor in speed and wait time
double calculateTravelCost(int x1, int y1, int x2, int y2) {
    double dist = calculateDistance(x1, y1, x2, y2);
    return dist / SPEED + WAIT_TIME;
}

// Generate a random integer in a range
int randInt(int low, int high) {
    std::random_device seed;
    std::mt19937 gen{ seed() };
    std::uniform_int_distribution<int> dist(low, high);
    int val = dist(gen);
    return val;
}
