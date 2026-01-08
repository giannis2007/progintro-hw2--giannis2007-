// recurse.c
// Reference: Adapted for HW2 Elevator Problem
// Author: <Your Name>
// Date: <Date>
// Source: Based on recursive approach described in assignment

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1000000

// Υπολογισμός κόστους για δεδομένες στάσεις
static int computeCost(int numPeople, int dests[], int stops[], int numStops) {
    int cost = 0;
    for (int i = 0; i < numPeople; i++) {
        int minDist = INF;
        for (int j = 0; j < numStops; j++) {
            int dist = abs(dests[i] - stops[j]);
            if (dist < minDist) minDist = dist;
        }
        cost += minDist;
    }
    return cost;
}

// Αναδρομική συνάρτηση
static void recursiveSolver(int numPeople, int numStopsLeft, int dests[], int maxFloor,
                            int stops[], int currentIndex, int *minCost, int bestStops[]) {

    if (numStopsLeft == 0) {
        int cost = computeCost(numPeople, dests, stops, currentIndex);
        if (cost < *minCost) {
            *minCost = cost;
            // Αντιγράφουμε τις στάσεις που δίνουν το min cost
            for (int i = 0; i < currentIndex; i++) {
                bestStops[i] = stops[i];
            }
        }
        return;
    }

    int start = 1;
    if (currentIndex > 0) start = stops[currentIndex - 1] + 1;

    for (int floor = start; floor <= maxFloor; floor++) {
        stops[currentIndex] = floor;
        recursiveSolver(numPeople, numStopsLeft - 1, dests, maxFloor,
                        stops, currentIndex + 1, minCost, bestStops);
    }
}

// Interface callable από elevate.c
// Επιστρέφει το minCost και γεμίζει lastStop με την τελευταία στάση
int recurseSolver(int numPeople, int numStops, int dests[], int *lastStop) {
    int maxFloor = 0;
    for (int i = 0; i < numPeople; i++) {
        if (dests[i] > maxFloor) maxFloor = dests[i];
    }

    int stops[numStops];
    int bestStops[numStops];
    int minCost = INF;

    recursiveSolver(numPeople, numStops, dests, maxFloor, stops, 0, &minCost, bestStops);

    if (numStops > 0) {
        *lastStop = bestStops[numStops - 1];  // τελευταία στάση
    } else {
        *lastStop = 0; // αν δεν υπάρχουν στάσεις
    }

    return minCost;
}
