#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, numProcesses, numResources;

    // Input for number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    // Initialize arrays for available resources, maximum demand, allocation, and need
    int available[numResources];
    int maxDemand[numProcesses][numResources];
    int allocation[numProcesses][numResources];
    int need[numProcesses][numResources];
    int visited[numProcesses];
    int safeSequence[numProcesses];

    // Input for available resources
    printf("Enter the available resources:\n");
    for (i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    // Input for each process's allocation and maximum demand
    for (i = 0; i < numProcesses; i++) {
        visited[i] = 0; // Initialize all processes as unvisited

        printf("Enter allocation for P%d: ", i + 1);
        for (j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }

        printf("Enter maximum demand for P%d: ", i + 1);
        for (j = 0; j < numResources; j++) {
            scanf("%d", &maxDemand[i][j]);
        }

        // Calculate the need matrix
        for (j = 0; j < numResources; j++) {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
        }
    }

    // Display the matrices
    printf("\nProcess\t  Max\t\tAllocation\tNeed\n");
    for (i = 0; i < numProcesses; i++) {
        printf("P%d\t", i + 1);

        // Display Max demand
        for (j = 0; j < numResources; j++) {
            printf("%d ", maxDemand[i][j]);
        }
        printf("\t\t");

        // Display Allocation
        for (j = 0; j < numResources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");

        // Display Need
        for (j = 0; j < numResources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Banker's Algorithm to find a safe sequence
    int completedProcesses = 0, sequenceIndex = 0;

    while (completedProcesses < numProcesses) {
        int foundSafeProcess = 0;

        for (i = 0; i < numProcesses; i++) {
            int canExecute = 1;

            // Check if the process can execute with available resources
            for (j = 0; j < numResources; j++) {
                if (need[i][j] > available[j]) {
                    canExecute = 0;
                    break;
                }
            }

            // If the process can execute and is not yet visited
            if (canExecute && !visited[i]) {
                // Add allocated resources back to available pool
                for (j = 0; j < numResources; j++) {
                    available[j] += allocation[i][j];
                }

                // Mark the process as visited and add to safe sequence
                visited[i] = 1;
                safeSequence[sequenceIndex++] = i;
                completedProcesses++;
                foundSafeProcess = 1;
            }
        }

        // If no process was found in this loop, system is in an unsafe state
        if (!foundSafeProcess) {
            printf("\nNo safe sequence found.\n");
            exit(0);
        }
    }

    // Print the safe sequence
    printf("\nSafe Sequence: < ");
    for (i = 0; i < numProcesses; i++) {
        printf("P%d ", safeSequence[i] + 1);
    }
    printf(">\n");

    return 0;
}
