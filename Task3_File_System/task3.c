
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char permission[4] = "rw-";

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

int login()
{
    char username[20];
    char password[20];

    printf("Username: ");
    scanf("%s",username);

    printf("Password: ");
    scanf("%s",password);

    if(strcmp(username,"admin")==0 &&
       strcmp(password,"1234")==0)
    {
        printf("\nLogin Successful.\n");
        return 1;
    }

    printf("\nInvalid Username or Password.\n");

    return 0;
}

void showPermission()
{
    printf("\nCurrent File Permission: %s\n", permission);
}


void changePermission()
{
    printf("\nEnter new permission (example rwx, rw-, r--): ");
    scanf("%s", permission);

    printf("Permission changed successfully.\n");
}


void checkReadPermission()
{
    if(permission[0]=='r')
        printf("Read Permission Granted.\n");
    else
        printf("Read Permission Denied.\n");
}


void checkWritePermission()
{
    if(permission[1]=='w')
        printf("Write Permission Granted.\n");
    else
        printf("Write Permission Denied.\n");
}


void checkExecutePermission()
{
    if(permission[2]=='x')
        printf("Execute Permission Granted.\n");
    else
        printf("Execute Permission Denied.\n");
}

int main()
{
    if(!login())
    {
        return 0;
    }
    int choice;
    do
    {
        printf("\n===== File System =====\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Show File Permission\n");
        printf("6. Change File Permission\n");
        printf("7. Check Read Permission\n");
        printf("8. Check Write Permission\n");
        printf("9. Check Execute Permission\n");
        printf("10. Exit\n");

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
                showPermission();
                break;


            case 6:
                changePermission();
                break;


            case 7:
                checkReadPermission();
                break;


            case 8:
                checkWritePermission();
                break;


            case 9:
                checkExecutePermission();
                break;
            default:
                printf("Invalid Choice.\n");
        }

    }while(choice!=10);

    return 0;
}
