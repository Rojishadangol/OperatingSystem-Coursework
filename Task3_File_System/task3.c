/*
    Task 3 - Day 14
    Basic File Operations
*/

#include <stdio.h>
#include <stdlib.h>

void createFile()
{
    FILE *fp = fopen("sample.txt", "w");

    if(fp == NULL)
    {
        printf("File could not be created.\n");
        return;
    }

    printf("File created successfully.\n");

    fclose(fp);
}

void writeFile()
{
    FILE *fp = fopen("sample.txt", "w");

    if(fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(fp,"Operating Systems Coursework\n");
    fprintf(fp,"Task 3 File System\n");

    fclose(fp);

    printf("Data written successfully.\n");
}

void readFile()
{
    FILE *fp = fopen("sample.txt","r");

    char ch;

    if(fp==NULL)
    {
        printf("File not found.\n");
        return;
    }

    printf("\nFile Content:\n\n");

    while((ch=fgetc(fp))!=EOF)
    {
        printf("%c",ch);
    }

    fclose(fp);
}

void deleteFile()
{
    if(remove("sample.txt")==0)
        printf("File deleted successfully.\n");
    else
        printf("Unable to delete file.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== File System =====\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createFile();
                break;

            case 2:
                writeFile();
                break;

            case 3:
                readFile();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice!=5);

    return 0;
}
