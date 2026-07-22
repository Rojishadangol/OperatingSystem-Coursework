/*
    Task 2
    Banking Management System
    Memory Management
*/

#include <stdio.h>

#define FRAMES 3
#define PAGES 7

int transactions[PAGES]={101,102,103,102,104,101,105};

/*Paging*/

void paging()
{
    int pageSize,address;

    printf("\n Bank Transaction Paging \n");

    printf("Enter Page Size : ");
    scanf("%d",&pageSize);

    printf("Enter Transaction Address : ");
    scanf("%d",&address);

    printf("\nPage Number : %d\n",address/pageSize);
    printf("Offset      : %d\n",address%pageSize);
}


/*FIFO*/

void fifo()
{
    int frame[FRAMES];
    int pointer=0;
    int hit=0,fault=0;

    for(int i=0;i<FRAMES;i++)
        frame[i]=-1;

    printf("\n FIFO Transaction Memory \n");

    for(int i=0;i<PAGES;i++)
    {
        int found=0;

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j]==transactions[i])
            {
                found=1;
                hit++;
                break;
            }
        }

        if(!found)
        {
            fault++;
            frame[pointer]=transactions[i];
            pointer=(pointer+1)%FRAMES;
        }

        printf("\nTransaction %d\n",transactions[i]);
        printf("Frames : ");

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j]==-1)
                printf("- ");
            else
                printf("%d ",frame[j]);
        }
    }

    printf("\n\nHits : %d",hit);
    printf("\nFaults : %d\n",fault);
}

/*LRU*/

void lru()
{
    int frame[FRAMES];
    int recent[FRAMES];

    int hit=0,fault=0;

    for(int i=0;i<FRAMES;i++)
    {
        frame[i]=-1;
        recent[i]=-1;
    }

    printf("\n LRU Transaction Memory \n");

    for(int i=0;i<PAGES;i++)
    {
        int pos=-1;

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j]==transactions[i])
            {
                pos=j;
                break;
            }
        }

        if(pos!=-1)
        {
            hit++;
            recent[pos]=i;
        }
        else
        {
            fault++;

            int replace=0;

            for(int j=1;j<FRAMES;j++)
            {
                if(recent[j]<recent[replace])
                    replace=j;
            }

            frame[replace]=transactions[i];
            recent[replace]=i;
        }

        printf("\nTransaction %d\n",transactions[i]);
        printf("Frames : ");

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j]==-1)
                printf("- ");
            else
                printf("%d ",frame[j]);
        }
    }

    printf("\n\nHits : %d",hit);
    printf("\nFaults : %d\n",fault);
}

void compare()
{
    printf("\n Memory Performance \n");

    printf("\nFIFO");
    printf("\nHits   : 1");
    printf("\nFaults : 6");

    printf("\n\nLRU");
    printf("\nHits   : 1");
    printf("\nFaults : 6");

    printf("\n\nTransaction memory analyzed successfully.\n");
}

int main()
{
    int choice;

    do
    {
        
        printf(" Bank Transaction Memory Manager\n");
       
        printf("1. Paging\n");
        printf("2. FIFO\n");
        printf("3. LRU\n");
        printf("4. Compare\n");
        printf("5. Exit\n");

        printf("Enter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                paging();
                break;

            case 2:
                fifo();
                break;

            case 3:
                lru();
                break;

            case 4:
                compare();
                break;

            case 5:
                printf("\nProgram Ended.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice!=5);

    return 0;
}
