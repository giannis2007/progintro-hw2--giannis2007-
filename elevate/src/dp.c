// dp.c
// Reference: HW2 Elevator Problem – Dynamic Programming approach
// Author: <Your Name>
// Date: <Date>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "elevate.h"

#define INF 1000000

// fw(a, b): κόστος για επιβάτες με προορισμούς (a, b]
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

// Dynamic Programming Solver
int dpSolver(int numPeople, int numStops, int dests[], int *lastStop) {
    int maxFloor = 0;
    for (int i = 0; i < numPeople; i++)
        if (dests[i] > maxFloor)
            maxFloor = dests[i];

    // M[i][j] = min cost με i στάσεις και τελευταία στον όροφο j
    int M[numStops + 1][maxFloor + 1];

    // Αρχικοποίηση
    for (int j = 0; j <= maxFloor; j++)
        M[0][j] = fw(0, -1, numPeople, dests);

    // DP υπολογισμός
    for (int i = 1; i <= numStops; i++) {
        for (int j = 0; j <= maxFloor; j++) {
            int best = INF;
            for (int k = 0; k <= j; k++) {
                int val = M[i - 1][k]
                        - fw(k, -1, numPeople, dests)
                        + fw(k, j, numPeople, dests)
                        + fw(j, -1, numPeople, dests);

                if (val < best)
                    best = val;
            }
            M[i][j] = best;
        }
    }

    // Εύρεση βέλτιστης τελευταίας στάσης
    int minCost = INF;
    int bestLast = 0;
    for (int j = 0; j <= maxFloor; j++) {
        if (M[numStops][j] < minCost) {
            minCost = M[numStops][j];
            bestLast = j;
        }
    }

    *lastStop = bestLast;
    return minCost;
}
