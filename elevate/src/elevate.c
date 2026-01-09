// elevate.c
// HW2 Elevator Problem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elevate.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr,
                "Usage: %s <inputfile> [--mode=recurse|brute|memoize|dp]\n",
                argv[0]);
        return 1;
    }

    char *inputFile = argv[1];
    char *mode = "dp";   // default mode

    if (argc >= 3 && strncmp(argv[2], "--mode=", 7) == 0) {
        mode = argv[2] + 7;
    }

    FILE *file = fopen(inputFile, "r");
    if (!file) {
        fprintf(stderr, "Cannot open input file %s\n", inputFile);
        return 1;
    }

    int numPeople, numStops;
    fscanf(file, "%d %d", &numPeople, &numStops);

    int dests[numPeople];
    for (int i = 0; i < numPeople; i++) {
        fscanf(file, "%d", &dests[i]);
    }

    fclose(file);

    int lastStop = 0;
    int minCost = 0;

    if (strcmp(mode, "recurse") == 0) {
        minCost = recurseSolver(numPeople, numStops, dests, &lastStop);
    }
    else if (strcmp(mode, "brute") == 0) {
        minCost = bruteSolver(numPeople, numStops, dests, &lastStop);
    }
    else if (strcmp(mode, "memoize") == 0) {
        minCost = memoizeSolver(numPeople, numStops, dests, &lastStop);
    }
    else if (strcmp(mode, "dp") == 0) {
        minCost = dpSolver(numPeople, numStops, dests, &lastStop);
    }
    else {
        fprintf(stderr, "Unknown mode: %s\n", mode);
        return 1;
    }

    /* Εκτύπωση αποτελέσματος σύμφωνα με την εκφώνηση */
    if (numStops == 0) {
        printf("No lift stops\n");
    } else {
        printf("Last stop at floor: %d\n", lastStop);
    }
    printf("The minimum cost is: %d\n", minCost);

    return 0;
}
