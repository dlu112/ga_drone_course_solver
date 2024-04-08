#pragma once
#include <iostream>
#include <random>

// Common structures
struct Coord {
    int x;
    int y;
};

struct Waypoint {
    int x;
    int y;
    int penalty;
};

// Global variables
extern double SPEED;
extern double WAIT_TIME;
extern Coord START_COORD;
extern Coord END_COORD;

extern std::vector<Waypoint> waypoints;

// Common functions
double calculateDistance(int x1, int y1, int x2, int y2);
double calculateTravelCost(int x1, int y1, int x2, int y2);
int randInt(int low, int high);
