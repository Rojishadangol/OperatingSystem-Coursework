/*
    Task 1
    Banking Management System
    Process Management and Threading
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 1000;
pthread_mutex_t lock;

void *depositService(void *arg)
{
    printf("\nDeposit Service Started.\n");

    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&lock);

        balance += 100;

        printf("Deposited Rs.100 | Balance = %d\n",balance);

        pthread_mutex_unlock(&lock);

        usleep(100000);
    }

    printf("Deposit Service Finished.\n");

    return NULL;
}

void *withdrawService(void *arg)
{
    printf("\nWithdrawal Service Started.\n");

    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&lock);

        balance -= 50;

        printf("Withdrawn Rs.50 | Balance = %d\n",balance);

        pthread_mutex_unlock(&lock);

        usleep(100000);
    }

    printf("Withdrawal Service Finished.\n");

    return NULL;
}

void *balanceService(void *arg)
{
    printf("\nBalance Inquiry Service Started.\n");

    for(int i=0;i<5;i++)
    {
        pthread_mutex_lock(&lock);

        printf("Current Balance = %d\n",balance);

        pthread_mutex_unlock(&lock);

        usleep(100000);
    }

    printf("Balance Inquiry Finished.\n");

    return NULL;
}

/*-----------------------------
    Round Robin Scheduling
------------------------------*/

void roundRobin()
{
    int bt[3] = {5,8,6};
    int rt[3];
    int ct[3], tat[3], wt[3];

    int tq = 2;
    int time = 0;
    int completed = 0;

    char process[3][25] =
    {
        "Deposit Service",
        "Withdrawal Service",
        "Balance Inquiry"
    };

    for(int i=0;i<3;i++)
        rt[i]=bt[i];

    printf("\n Round Robin Scheduling \n");

    while(completed<3)
    {
        for(int i=0;i<3;i++)
        {
            if(rt[i]>0)
            {
                if(rt[i]>tq)
                {
                    printf("%s executes from %d to %d\n",
                    process[i],time,time+tq);

                    time+=tq;
                    rt[i]-=tq;
                }
                else
                {
                    printf("%s finished.\n",process[i]);

                    time+=rt[i];
                    rt[i]=0;

                    ct[i]=time;
                    completed++;
                }
            }
        }
    }

    printf("\n-----------------------------------------\n");
    printf("Service\t\tCT\tTAT\tWT\n");
    printf("-----------------------------------------\n");

    for(int i=0;i<3;i++)
    {
        tat[i]=ct[i];
        wt[i]=tat[i]-bt[i];

        printf("%d\t\t%d\t%d\t%d\n",
        i+1,ct[i],tat[i],wt[i]);
    }
}

/*-----------------------------
    Deadlock Prevention
------------------------------*/

pthread_mutex_t accountLock;
pthread_mutex_t databaseLock;

void *transactionModule(void *arg)
{
    printf("\nTransaction Module waiting for Account Lock...\n");

    pthread_mutex_lock(&accountLock);

    sleep(1);

    pthread_mutex_lock(&databaseLock);

    printf("Transaction Module Processing...\n");

    pthread_mutex_unlock(&databaseLock);
    pthread_mutex_unlock(&accountLock);

    printf("Transaction Module Finished.\n");

    return NULL;
}

void *databaseModule(void *arg)
{
    printf("\nDatabase Module waiting for Account Lock...\n");

    pthread_mutex_lock(&accountLock);

    sleep(1);

    pthread_mutex_lock(&databaseLock);

    printf("Database Module Updating Records...\n");

    pthread_mutex_unlock(&databaseLock);
    pthread_mutex_unlock(&accountLock);

    printf("Database Module Finished.\n");

    return NULL;
}

void deadlockDemo()
{
    pthread_t t1,t2;

    pthread_mutex_init(&accountLock,NULL);
    pthread_mutex_init(&databaseLock,NULL);

    pthread_create(&t1,NULL,transactionModule,NULL);
    pthread_create(&t2,NULL,databaseModule,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&accountLock);
    pthread_mutex_destroy(&databaseLock);

    printf("\nDeadlock avoided using same lock order.\n");
}

int main()
{
    int choice;

    do
    {
        
        printf("   Banking Management System\n");
        
        printf("1. Banking Services (Threads)\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Deadlock Prevention\n");
        printf("4. Exit\n");

        printf("Enter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            {
                pthread_t t1,t2,t3;

                pthread_mutex_init(&lock,NULL);

                printf("\nStarting Banking Services...\n");

                pthread_create(&t1,NULL,depositService,NULL);
                pthread_create(&t2,NULL,withdrawService,NULL);
                pthread_create(&t3,NULL,balanceService,NULL);

                pthread_join(t1,NULL);
                pthread_join(t2,NULL);
                pthread_join(t3,NULL);

                pthread_mutex_destroy(&lock);

                printf("\nFinal Account Balance : %d\n",balance);

                printf("Synchronization using mutex completed.\n");
                printf("All banking services completed.\n");

                break;
            }

            case 2:
                roundRobin();
                break;

            case 3:
                deadlockDemo();
                break;

            case 4:
                printf("\nProgram Ended.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice!=4);

    return 0;
}

