#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000

/*
 * Υπολογίζει το συνολικό κόστος για ένα συγκεκριμένο σύνολο στάσεων.
 * Για κάθε επιβάτη υπολογίζεται η απόσταση από την κοντινότερη στάση.
 */
int computeCost(int numPeople, int dests[], int stops[], int numStops) {
    int cost = 0;

    for (int i = 0; i < numPeople; i++) {
        int minDist = INF;
        for (int j = 0; j < numStops; j++) {
            int dist = abs(dests[i] - stops[j]);
            if (dist < minDist)
                minDist = dist;
        }
        cost += minDist;
    }

    return cost;
}

/*
 * Αναδρομική brute-force παραγωγή όλων των δυνατών συνδυασμών στάσεων.
 * Οι στάσεις είναι αυστηρά αύξουσες για να αποφεύγονται διπλότυπα.
 */
void tryStops(int numPeople, int dests[], int maxFloor,
              int stops[], int index, int left,
              int bestStops[], int *minCost) {

    if (left == 0) {
        int cost = computeCost(numPeople, dests, stops, index);
        if (cost < *minCost) {
            *minCost = cost;
            for (int i = 0; i < index; i++)
                bestStops[i] = stops[i];
        }
        return;
    }

    int start = (index == 0) ? 1 : stops[index - 1] + 1;

    for (int f = start; f <= maxFloor; f++) {
        stops[index] = f;
        tryStops(numPeople, dests, maxFloor,
                 stops, index + 1, left - 1,
                 bestStops, minCost);
    }
}

/*
 * Κύρια brute-force μέθοδος
 */
void bruteForce(int numPeople, int dests[], int numStops) {

    /* Περίπτωση χωρίς στάσεις */
    if (numStops == 0) {
        int cost = 0;
        for (int i = 0; i < numPeople; i++)
            cost += dests[i];

        printf("No lift stops\n");
        printf("The minimum cost is: %d\n", cost);
        return;
    }

    int maxFloor = 0;
    for (int i = 0; i < numPeople; i++)
        if (dests[i] > maxFloor)
            maxFloor = dests[i];

    int stops[numStops];
    int bestStops[numStops];
    int minCost = INF;

    tryStops(numPeople, dests, maxFloor,
             stops, 0, numStops,
             bestStops, &minCost);

    printf("Lift stops are: ");
    for (int i = 0; i < numStops; i++)
        printf("%d ", bestStops[i]);
    printf("\n");

    printf("The minimum cost is: %d\n", minCost);
}
