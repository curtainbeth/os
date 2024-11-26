#include <stdio.h>

int main() {
    int n, at[10], bt[10], wt[10], tat[10], ct[10], pr[10];
    int sum = 0, i, j, pos, temp;
    float totaltat = 0, totalwt = 0;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    // Input Arrival Time
    printf("\nEnter the Arrival Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Arrival Time of Process[%d]: ", i + 1);
        scanf("%d", &at[i]);
    }

    // Input Burst Time
    printf("\nEnter the Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst Time of Process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Input Priority
    printf("\nEnter the Priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Priority of Process[%d]: ", i + 1);
        scanf("%d", &pr[i]);
    }

    // Sort processes by priority and arrival time (Selection Sort)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos] || (pr[j] == pr[pos] && at[j] < at[pos])) { 
                // Higher priority or earlier arrival time
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

        // Swap arrival time
        temp = at[i];
        at[i] = at[pos];
        at[pos] = temp;
    }

    // Calculate Completion Time (CT)
    sum = 0;
    for (i = 0; i < n; i++) {
        if (sum < at[i]) {
            sum = at[i]; // Wait for the process to arrive
        }
        sum += bt[i];
        ct[i] = sum; // Completion time
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  // TAT = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i]; // WT = Turnaround Time - Burst Time
        totaltat += tat[i];
        totalwt += wt[i];
    }

    // Print the results
    printf("\nProcess\tPriority\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", i + 1, pr[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Print averages
    printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
    printf("Average Waiting Time: %.2f\n", totalwt / n);

    return 0;
}
