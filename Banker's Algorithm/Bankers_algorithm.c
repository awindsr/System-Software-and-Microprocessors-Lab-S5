#include <stdio.h>
#include <stdlib.h>

void main() {
    int numProcesses, numResources;
    int isSafeSequenceFound = 0, completedProcessesCount = 0, sequenceIndex = 0;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    // Input the number of resources
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    // Arrays to hold allocation, maximum demand, need, available resources, safe sequence, and visited status
    int allocation[numProcesses][numResources];
    int maxDemand[numProcesses][numResources];
    int need[numProcesses][numResources];
    int available[numResources];
    int safeSequence[numProcesses];
    int visited[numProcesses];

    // Input the allocation matrix for each process
    printf("Enter the allocation for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input the maximum demand matrix for each process
    printf("Enter the maximum demand for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        visited[i] = 0; // Initialize visited status
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &maxDemand[i][j]);
        }
    }

    // Calculate the need matrix for each process
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
        }
    }

    // Input the available resources
    printf("Enter the available resources for each allocation: ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    // Display the allocation, maximum demand, available resources, and need matrix
    printf("ALLOCATION   MAX   AVAILABLE   NEED\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            printf(" %d ", allocation[i][j]);
        }
        for (int j = 0; j < numResources; j++) {
            printf("  %d", maxDemand[i][j]);
        }
        printf(" ");
        for (int j = 0; j < numResources; j++) {
            printf("  %d", available[j]);
        }
        printf("   ");
        for (int j = 0; j < numResources; j++) {
            printf(" %d ", need[i][j]);
        }
        printf("\n");
    }

    // Main loop to find the safe sequence
    while (completedProcessesCount < numProcesses) {
        isSafeSequenceFound = 0; // Reset flag for this iteration

        // Check each process to see if it can be executed
        for (int i = 0; i < numProcesses; i++) {
            int canExecute = 1; // Assume process can execute

            // Check if all needed resources are available
            for (int j = 0; j < numResources; j++) {
                if (need[i][j] > available[j]) {
                    canExecute = 0; // Process cannot execute
                    break;
                }
            }

            // If process can execute and hasn't been visited yet
            if (canExecute && visited[i] == 0) {
                // Release the allocated resources back to the available pool
                for (int j = 0; j < numResources; j++) {
                    available[j] += allocation[i][j];
                }
                visited[i] = 1; // Mark process as visited
                safeSequence[sequenceIndex++] = i; // Add to safe sequence
                completedProcessesCount++; // Increment completed process count
                isSafeSequenceFound = 1; // Mark that we found a safe sequence
            }
        }

        // If no process was able to execute, the system is not in a safe state
        if (isSafeSequenceFound == 0) {
            printf("\nThere is no Safe Sequence\n");
            exit(0);
        }
    }

    // Output the safe sequence
    printf("\nSafe Sequence = <");
    for (int i = 0; i < sequenceIndex; i++) {
        printf("P%d ", safeSequence[i]); // Print each process in the safe sequence
    }
    printf(">\n");
}
