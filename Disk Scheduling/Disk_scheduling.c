#include <stdio.h>
#include <stdlib.h>

void fcfs(int numOfRequests, int requests[]);
void scan(int numOfRequests, int requests[], int head, int size);
void cscan(int numOfRequests, int requests[], int head, int size);

int main() {
    int numOfRequests, size, head, choice;

    printf("Enter the number of requests: ");
    scanf("%d", &numOfRequests);

    int requests[numOfRequests + 1];  
    printf("Enter the head position: ");
    scanf("%d", &head);
    requests[0] = head;

    printf("Enter the max size of disk: ");
    scanf("%d", &size);

    for (int i = 1; i <= numOfRequests; i++) {
        printf("Enter request number %d: ", i);
        scanf("%d", &requests[i]);
    }

    do {
        printf("Choose the algorithm to use\n1.FCFS 2.Scan 3.C-Scan\n0.Exit: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(numOfRequests, requests);
                break;
            case 2:
                scan(numOfRequests, requests, head, size);
                break;
            case 3:
                cscan(numOfRequests, requests, head, size);
                break;
            case 0:
                printf("Exiting..\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, 3, or 0.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

void fcfs(int numOfRequests, int requests[]) {
    int seekTime = 0;
    int currentPosition = requests[0];

    for (int i = 1; i <= numOfRequests; i++) {
        seekTime += abs(requests[i] - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, requests[i]);
        currentPosition = requests[i];
    }
    printf("Seek time: %d\n", seekTime);
}

void scan(int numOfRequests, int requests[], int head, int size) {
    int seekTime = 0;
    int index;

    // Sorting requests
    for (int i = 1; i <= numOfRequests; i++) {
        for (int j = i + 1; j <= numOfRequests; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Find index of head
    for (index = 1; index <= numOfRequests; index++) {
        if (requests[index] >= head) {
            break;
        }
    }

    // Process requests in the increasing direction from head
    int currentPosition = head;
    printf("Disk moved from %d to %d\n", currentPosition, requests[index]);
    seekTime += abs(requests[index] - currentPosition);
    currentPosition = requests[index];

    for (int i = index + 1; i <= numOfRequests; i++) {
        seekTime += abs(requests[i] - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, requests[i]);
        currentPosition = requests[i];
    }

    // Move to the end of the disk
    if (currentPosition != size - 1) {
        seekTime += abs(size - 1 - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, size - 1);
        currentPosition = size - 1;
    }

    // Move to the start of the disk
    if (currentPosition != 0) {
        seekTime += size - 1;
        printf("Disk moved from %d to %d\n", currentPosition, 0);
        currentPosition = 0;
    }

    // Process requests from start to initial index
    for (int i = 1; i < index; i++) {
        seekTime += abs(requests[i] - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, requests[i]);
        currentPosition = requests[i];
    }

    printf("Seek time: %d\n", seekTime);
}

void cscan(int numOfRequests, int requests[], int head, int size) {
    int seekTime = 0;
    int index;

    // Sorting requests
    for (int i = 1; i <= numOfRequests; i++) {
        for (int j = i + 1; j <= numOfRequests; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Find index of head
    for (index = 1; index <= numOfRequests; index++) {
        if (requests[index] >= head) {
            break;
        }
    }

    // Process requests from head to end of disk
    int currentPosition = head;
    if (index <= numOfRequests) {
        printf("Disk moved from %d to %d\n", currentPosition, requests[index]);
        seekTime += abs(requests[index] - currentPosition);
        currentPosition = requests[index];
    }

    for (int i = index + 1; i <= numOfRequests; i++) {
        seekTime += abs(requests[i] - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, requests[i]);
        currentPosition = requests[i];
    }

    // Move to the end of the disk and wrap around to the start
    if (currentPosition < size - 1) {
        seekTime += abs(size - 1 - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, size - 1);
        currentPosition = 0; // Wrap around to start
        seekTime += size - 1;
        printf("Disk moved from %d to %d\n", size - 1, 0);
    }

    // Process requests from start to the initial index
    for (int i = 1; i < index; i++) {
        seekTime += abs(requests[i] - currentPosition);
        printf("Disk moved from %d to %d\n", currentPosition, requests[i]);
        currentPosition = requests[i];
    }

    printf("Seek time: %d\n", seekTime);
}

