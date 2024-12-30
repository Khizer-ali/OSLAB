#include <stdio.h>
#include <stdbool.h>

// Function to check if the system is in a safe state
bool isSafeState(int processes, int resources, int available[], int max[][resources], int allocation[][resources]) {
    int need[processes][resources];
    int work[resources];
    bool finish[processes];

    // Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize Work and Finish arrays
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    // Safety algorithm
    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;

                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false; // Deadlock detected
        }
    }

    return true; // Safe state
}

int main() {
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int available[resources];
    int max[processes][resources];
    int allocation[processes][resources];

    printf("Enter the Available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the Max resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    if (isSafeState(processes, resources, available, max, allocation)) {
        printf("The system is in a SAFE state.\n");
    } else {
        printf("The system is in an UNSAFE state (deadlock may occur).\n");
    }

    return 0;
}
