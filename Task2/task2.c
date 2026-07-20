/*
    Task 2 - Memory Management
*/

#include <stdio.h>

#define FRAMES 3
#define PAGES 7

int pages[PAGES] = {1,2,3,2,4,1,5};

void paging()
{
    int pageSize;
    int logicalAddress;

    printf("\n Paging System\n");

    printf("Enter Page Size: ");
    scanf("%d", &pageSize);

    printf("Enter Logical Address: ");
    scanf("%d", &logicalAddress);

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    printf("\nAddress Translation\n");

    printf("\nPage Size        : %d\n", pageSize);
    printf("Logical Address  : %d\n", logicalAddress);
    printf("Page Number      : %d\n", pageNumber);
    printf("Offset           : %d\n", offset);
}

void fifo()
{
    int frame[FRAMES];
    int pointer = 0;
    int hit = 0;
    int fault = 0;

    for(int i=0;i<FRAMES;i++)
        frame[i] = -1;

    printf("\n FIFO Page Replacement \n");

    for(int i=0;i<PAGES;i++)
    {
        int found = 0;

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(found)
        {
            hit++;
        }
        else
        {
            fault++;
            frame[pointer] = pages[i];
            pointer = (pointer + 1) % FRAMES;
        }

        printf("\nPage %d: \n", pages[i]);

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        printf("\n");
    }

    printf("\nHits        : %d\n", hit);
    printf("Page Faults : %d\n", fault);
    printf("Hit Ratio   : %.2f\n",(float)hit/PAGES);
    printf("Miss Ratio  : %.2f\n",(float)fault/PAGES);
}

void lru()
{
    int frame[FRAMES];
    int recent[FRAMES];

    int hit = 0;
    int fault = 0;

    for(int i=0;i<FRAMES;i++)
    {
        frame[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement \n");

    for(int i=0;i<PAGES;i++)
    {
        int found = -1;

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j] == pages[i])
            {
                found = j;
                break;
            }
        }

        if(found != -1)
        {
            hit++;
            recent[found] = i;
        }
        else
        {
            fault++;

            int replace = 0;

            for(int j=1;j<FRAMES;j++)
            {
                if(recent[j] < recent[replace])
                    replace = j;
            }

            frame[replace] = pages[i];
            recent[replace] = i;
        }

        printf("\nPage %d: \n", pages[i]);

        for(int j=0;j<FRAMES;j++)
        {
            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        printf("\n");
    }
    printf("\nHits        : %d\n", hit);
    printf("Page Faults : %d\n", fault);
    printf("Hit Ratio   : %.2f\n",(float)hit/PAGES);
    printf("Miss Ratio  : %.2f\n",(float)fault/PAGES);
}

int main()
{
    int choice;

    do
    {
        
        printf("   MEMORY MANAGEMENT SIMULATOR\n");
        
        printf("1. Paging System\n");
        printf("2. FIFO Page Replacement\n");
        printf("3. LRU Page Replacement\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
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
                printf("\nProgram Ended.\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    }while(choice!=4);

    return 0;
}
