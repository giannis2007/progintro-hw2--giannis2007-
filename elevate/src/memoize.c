// memoize.c
// Reference: HW2 Elevator Problem – Memoization approach
// Author: <Your Name>
// Date: <Date>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "elevate.h"

#define INF 1000000

// Υπολογισμός fw(a, b)
static int fw(int a, int b, int numPeople, int dests[]) {
    int cost = 0;
    for (int i = 0; i < numPeople; i++) {
        int d = dests[i];
        if (d > a && (b == -1 || d <= b)) {
            int mid = (b == -1) ? a : (a + b) / 2;
            if (d <= mid)
                cost += d - a;
            else
                cost += b - d;
        }
    }
    return cost;
}

// Memoized recursive function
static int solve(int i, int j, int numPeople, int numStops,
                 int dests[], int memo[][1001]) {

    if (memo[i][j] != -1)
        return memo[i][j];

    if (i == 0) {
        memo[i][j] = fw(0, -1, numPeople, dests);
        return memo[i][j];
    }

    int best = INF;
    for (int k = 0; k <= j; k++) {
        int val = solve(i - 1, k, numPeople, numStops, dests, memo)
                - fw(k, -1, numPeople, dests)
                + fw(k, j, numPeople, dests)
                + fw(j, -1, numPeople, dests);

        if (val < best)
            best = val;
    }

    memo[i][j] = best;
    return best;
}

// Interface για elevate.c
int memoizeSolver(int numPeople, int numStops, int dests[], int *lastStop) {
    int maxFloor = 0;
    for (int i = 0; i < numPeople; i++)
        if (dests[i] > maxFloor)
            maxFloor = dests[i];

    static int memo[51][1001];
    for (int i = 0; i <= numStops; i++)
        for (int j = 0; j <= maxFloor; j++)
            memo[i][j] = -1;

    int minCost = INF;
    int bestLast = 0;

    for (int j = 0; j <= maxFloor; j++) {
        int cost = solve(numStops, j, numPeople, numStops, dests, memo);
        if (cost < minCost) {
            minCost = cost;
            bestLast = j;
        }
    }

    *lastStop = bestLast;
    return minCost;
}
