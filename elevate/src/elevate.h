#ifndef ELEVATE_H
#define ELEVATE_H

// Recursive solution
int recurseSolver(int numPeople, int numStops, int dests[], int *lastStop);

// Brute-force solution
int bruteSolver(int numPeople, int numStops, int dests[], int *lastStop);

// Memoization solution
int memoizeSolver(int numPeople, int numStops, int dests[], int *lastStop);

// Dynamic programming solution
int dpSolver(int numPeople, int numStops, int dests[], int *lastStop);

#endif
