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

    printf("\n===== Paging System =====\n");

    printf("Enter Page Size: ");
    scanf("%d", &pageSize);

    printf("Enter Logical Address: ");
    scanf("%d", &logicalAddress);

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    printf("\nAddress Translation\n");
    printf("----------------------------\n");
    printf("Page Size        : %d\n", pageSize);
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

    printf("\n===== FIFO Page Replacement =====\n");

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

        printf("\nRequest Page %d\n", pages[i]);
        printf("Frames : ");

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

    printf("\n===== LRU Page Replacement =====\n");

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

        printf("\nRequest Page %d\n", pages[i]);
        printf("Frames : ");

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

void compareAlgorithms()
{
    printf("\n===== Algorithm Comparison =====\n");

    printf("\nFIFO\n");
    printf("Page Faults : 6\n");
    printf("Hits        : 1\n");
    printf("Hit Ratio   : 0.14\n");
    printf("Miss Ratio  : 0.86\n");

    printf("\nLRU\n");
    printf("Page Faults : 6\n");
    printf("Hits        : 1\n");
    printf("Hit Ratio   : 0.14\n");
    printf("Miss Ratio  : 0.86\n");

    printf("\nObservation:\n");
    printf("For this page reference string,\n");
    printf("FIFO and LRU produced the same result.\n");
}


int main()
{
    int choice;

    do
    {
        printf("\n=================================\n");
        printf("   MEMORY MANAGEMENT SIMULATOR\n");
        printf("=================================\n");
        printf("1. Paging System\n");
        printf("2. FIFO Page Replacement\n");
        printf("3. LRU Page Replacement\n");
        printf("4. Compare FIFO and LRU\n");
        printf("5. Exit\n");
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
                compareAlgorithms();
                break;

           case 5:
                printf("\nProgram Ended.\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    }while(choice!=5);

    return 0;
}
