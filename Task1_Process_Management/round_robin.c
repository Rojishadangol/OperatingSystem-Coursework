#include <stdio.h>

int main()
{
    int n = 3;
    int burstTime[3] = {5,8,6};
    int remainingTime[3];
    int ct[3];
    int tat[3];
    int wt[3];
    int timeQuantum = 2;
    int i;
    int time = 0;
    int completed = 0;
    float avgWT = 0;
    float avgTAT = 0;

    for(i = 0; i < n; i++)
    {
        remainingTime[i] = burstTime[i];
    }

    printf("Round Robin Scheduling. \n");
    printf("Time Quantum = %d\n\n", timeQuantum);

    while(completed < n)
    {
        
        for(i = 0; i < n; i++){
            if(remainingTime[i] > 0){
                
                if(remainingTime[i] > timeQuantum){
                    printf("Process p%d executes for %d units\n", i + 1, timeQuantum);
                    time += timeQuantum; 
                    remainingTime[i] -= timeQuantum;
                }
                else{
                    printf("Process P%d executes for %d units and finishes\n", i + 1, remainingTime[i]);
                    time += remainingTime[i];
                    remainingTime[i] = 0;
                    ct[i] = 0;
                    completed++;
                }
            }
       }
    }
    printf("\n");
 
    printf("----------------------------------------\n");
    printf("Process\tBT\tCT\tTAT\tWT\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i];
        wt[i] = tat[i] - burstTime[i];

        avgWT += wt[i];
        avgTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\n", 
            i + 1,
            burstTime[i],
            ct[i],
            tat[i],
            wt[i]
        );
    }
    avgWT /= n;
    avgTAT /= n;
    printf("----------------------------------------\n");
    printf("Average Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);

    return 0;
}
