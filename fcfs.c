#include <stdio.h>

int main() {
   int n, at[10], bt[10], wt[10], tat[10], ct[10], sum, i, j, k;
   float totaltat = 0, totalwt = 0;

   // Input the number of processes
   printf("Enter the total number of processes: ");
   scanf("%d", &n);

   printf("\nEnter the Process Arrival Time & Burst Time:\n");
   for (i = 0; i < n; i++) {
       printf("Enter Arrival time of process[%d]: ", i + 1);
       scanf("%d", &at[i]);
       printf("Enter Burst time of process[%d]: ", i + 1);
       scanf("%d", &bt[i]);
   }

   // Calculate completion time of processes
   sum = at[0];  // Assume processes start arriving at the same time
   for (j = 0; j < n; j++) {
       sum = sum + bt[j];
       ct[j] = sum;  // Completion time
   }

   // Calculate Turnaround Time (TAT)
   for (k = 0; k < n; k++) {
       tat[k] = ct[k] - at[k];  // TAT = CT - AT
       totaltat = totaltat + tat[k];
   }

   // Calculate Waiting Time (WT)
   for (k = 0; k < n; k++) {
       wt[k] = tat[k] - bt[k];  // WT = TAT - BT
       totalwt = totalwt + wt[k];
   }

   // Print the results
   printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
   for (i = 0; i < n; i++) {
       printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
   }

   // Print average TAT and WT
   printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
   printf("Average Waiting Time: %.2f\n", totalwt / n);

   return 0;
}
