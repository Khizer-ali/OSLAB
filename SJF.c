#include <stdio.h>

void sjf(int n, int arrival[], int burst[]) {
    int wait[n], turnaround[n], completion[n], visited[n];
    int total_wait = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++) visited[i] = 0;

    int time = 0, completed = 0;

    while (completed < n) {
        int min_burst = 100000, idx = -1;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && !visited[i] && burst[i] < min_burst) {
                min_burst = burst[i];
                idx = i;
            }
        }

        if (idx != -1) {
            completion[idx] = time + burst[idx];
            turnaround[idx] = completion[idx] - arrival[idx];
            wait[idx] = turnaround[idx] - burst[idx];

            time = completion[idx];
            visited[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrival[i], burst[i], completion[i], wait[i], turnaround[i]);
        total_wait += wait[i];
        total_turnaround += turnaround[i];
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround / n);
}

int main() {
    int n;
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

    sjf(n, arrival, burst);
    return 0;
}
