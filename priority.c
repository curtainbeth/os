#include <stdio.h>

int main() {
    int n, at[10], bt[10], wt[10], tat[10], ct[10], pr[10];
    int sum = 0, i, j, pos, temp;
    float totaltat = 0, totalwt = 0;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    // Input Burst Time
    printf("\nEnter the Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Input Priority
    printf("\nEnter the Priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Priority of Process[%d]: ", i + 1);
        scanf("%d", &pr[i]);
    }

    // Sort processes by priority (Selection Sort)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos]) { // Higher priority (smaller number) comes first
                pos = j;
            }
        }
        // Swap priority
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
    }

    // Calculate Completion Time (CT)
    for (i = 0; i < n; i++) {
        sum += bt[i];
        ct[i] = sum; // Completion time
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (i = 0; i < n; i++) {
        tat[i] = ct[i]; // Assuming AT = 0
        wt[i] = tat[i] - bt[i];
        totaltat += tat[i];
        totalwt += wt[i];
    }

    // Print the results
    printf("\nProcess\tPriority\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\t%d\n", i + 1, pr[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
    printf("Average Waiting Time: %.2f\n", totalwt / n);

    return 0;
}
