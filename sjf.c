#include<stdio.h>

int main() {
    int n, at[10], bt[10], wt[10], tat[10], ct[10], p[10], sum = 0, i, j, temp;
    float totaltat = 0, totalwt = 0;

    // Input the total number of processes
    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    // Input process numbers
    printf("\nEnter the process numbers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // Input Burst Times
    printf("\nEnter The Process Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("Enter Burst time of process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sort processes by Burst Time using Bubble Sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                // Swap Burst Time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap Process Number
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time
    for (i = 0; i < n; i++) {
        sum += bt[i];
        ct[i] = sum; // Completion Time for each process
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (i = 0; i < n; i++) {
        tat[i] = ct[i];          // TAT = Completion Time (since AT = 0)
        wt[i] = tat[i] - bt[i];  // WT = TAT - Burst Time
        totaltat += tat[i];      // Sum of TATs
        totalwt += wt[i];        // Sum of WTs
    }

    // Print the results
    printf("\nProcess\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Print average Turnaround Time and Waiting Time
    printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
    printf("Average Waiting Time: %.2f\n", totalwt / n);

    return 0;
}
