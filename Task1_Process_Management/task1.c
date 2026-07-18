#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 1000;
pthread_mutex_t lock;
pthread_mutex_t lock1, lock2;

/* Thread Synchronization */

void *deposit(void *arg)
{
    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&lock);
        balance += 100;
        printf("Deposit : %d\n", balance);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *withdraw(void *arg)
{
    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&lock);
        balance -= 50;
        printf("Withdraw: %d\n", balance);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *showBalance(void *arg)
{
    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&lock);
        printf("Balance : %d\n", balance);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void threadDemo()
{
    pthread_t t1,t2,t3;

    pthread_mutex_init(&lock,NULL);

    balance = 1000;

    printf("\nInitial Balance = %d\n\n",balance);

    pthread_create(&t1,NULL,deposit,NULL);
    pthread_create(&t2,NULL,withdraw,NULL);
    pthread_create(&t3,NULL,showBalance,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    printf("\nFinal Balance = %d\n",balance);

    pthread_mutex_destroy(&lock);
}

/* Round Robin  */

void roundRobin()
{
    int bt[3]={5,8,6};
    int rt[3],ct[3],tat[3],wt[3];

    int tq=2,time=0,done=0;

    float avgWT=0,avgTAT=0;

    for(int i=0;i<3;i++)
        rt[i]=bt[i];

    printf("\nRound Robin Scheduling\n\n");

    while(done<3)
    {
        for(int i=0;i<3;i++)
        {
            if(rt[i]>0)
            {
                if(rt[i]>tq)
                {
                    printf("P%d : %d units\n",i+1,tq);
                    time+=tq;
                    rt[i]-=tq;
                }
                else
                {
                    printf("P%d : %d units (Finished)\n",i+1,rt[i]);
                    time+=rt[i];
                    rt[i]=0;
                    ct[i]=time;
                    done++;
                }
            }
        }
    }

    printf("\nProcess\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<3;i++)
    {
        tat[i]=ct[i];
        wt[i]=tat[i]-bt[i];

        avgWT+=wt[i];
        avgTAT+=tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\n",
               i+1,bt[i],ct[i],tat[i],wt[i]);
    }

    printf("Average WT : %.2f\n",avgWT/3);
    printf("Average TAT: %.2f\n",avgTAT/3);
}

/*  Deadlock Prevention */

void *thread1(void *arg)
{
    pthread_mutex_lock(&lock1);
    printf("Thread 1 acquired Lock 1\n");

    sleep(1);

    pthread_mutex_lock(&lock2);
    printf("Thread 1 acquired Lock 2\n");

    printf("Thread 1 Working...\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

void *thread2(void *arg)
{
    pthread_mutex_lock(&lock1);
    printf("Thread 2 acquired Lock 1\n");

    sleep(1);

    pthread_mutex_lock(&lock2);
    printf("Thread 2 acquired Lock 2\n");

    printf("Thread 2 Working...\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

void deadlockDemo()
{
    pthread_t t1,t2;

    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);

    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("\nDeadlock avoided by locking resources in the same order.\n");
}

/*  Main  */

int main()
{
    int choice;

    do
    {
        printf("Task 1 - Process Management\n");
        printf("1. Thread Synchronization\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Deadlock Prevention\n");
        printf("4. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                threadDemo();
                break;

            case 2:
                roundRobin();
                break;

            case 3:
                deadlockDemo();
                break;

            case 4:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice!=4);

    return 0;
}
