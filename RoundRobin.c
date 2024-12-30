#include <stdio.h>

void round_robin(int n, int arrival[], int burst[], int quantum) {
    int remaining[n], wait[n], turnaround[n];
    int time = 0, completed = 0;
    int total_wait = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++) remaining[i] = burst[i];

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                if (remaining[i] <= quantum) {
                    time += remaining[i];
                    remaining[i] = 0;
                    turnaround[i] = time - arrival[i];
                    wait[i] = turnaround[i] - burst[i];
                    completed++;
                } else {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                executed = 1;
            }
        }
        if (!executed) time++;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, arrival[i], burst[i], wait[i], turnaround[i]);
        total_wait += wait[i];
        total_turnaround += turnaround[i];
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n];
    printf("Enter arrival times and burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Process %d - Burst: ", i + 1);
        scanf("%d", &burst[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    round_robin(n, arrival, burst, quantum);
    return 0;
}
