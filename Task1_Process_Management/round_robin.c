#include <stdio.h>

int main()
{
    int burstTime[3] = {5,8,6};
    int remainingTime[3];
    int timeQuantum = 2;
    int i;
    int completed;

    for(i = 0; i < 3; i++)
    {
        remainingTime[i] = burstTime[i];
    }

    printf("Round Robin Scheduling. \n");
    printf("Time Quantum = %d\n\n", timeQuantum);

    do {
        completed = 1;
        for(i = 0; i < 3; i++){
            if(remainingTime[i] > 0){
                completed = 0;

                if(remainingTime[i] > timeQuantum){
                    printf("Process p%d executes for %d units\n", i + 1, timeQuantum);
                    remainingTime[i] -= timeQuantum;
                }
                else{
                    printf("Process P%d executes for %d units and finishes\n", i + 1, remainingTime[i]);
                    remainingTime[i] = 0;
                }
            }
       }
    }
    while(!completed);
    printf("\n All processes completed. \n");
    return 0;

}
