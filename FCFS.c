#include <stdio.h>

void fcfs(int n, int arrival[], int burst[]) {
    int wait[n], turnaround[n], completion[n];
    int total_wait = 0, total_turnaround = 0;

    completion[0] = arrival[0] + burst[0];
    wait[0] = 0;
    turnaround[0] = burst[0];

    for (int i = 1; i < n; i++) {
        if (arrival[i] > completion[i - 1]) {
            completion[i] = arrival[i] + burst[i];
        } else {
            completion[i] = completion[i - 1] + burst[i];
        }
        turnaround[i] = completion[i] - arrival[i];
        wait[i] = turnaround[i] - burst[i];
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

    fcfs(n, arrival, burst);
    return 0;
}
