#include <stdio.h>
#include <string.h>

char samplePermission[4] = "rw-";
char readOnlyPermission[4] = "r--";


void writeLog(char action[])
{
    FILE *log = fopen("audit.log", "a");

    if(log == NULL)
    {
        printf("Unable to create log file.\n");
        return;
    }

    fprintf(log, "%s\n", action);

    fclose(log);
}

void createFile()
{
    FILE *fp = fopen("sample.txt", "w");
    FILE *fp2 = fopen("reaaonly.txt", "w");

    if(fp == NULL || fp2 == NULL)
    {
        printf("File could not be created.\n");
        return;
    }

    fprintf(fp, "Operating Systems Coursework\n");
    fprintf(fp, "Owner: Admin\n");
    fprintf(fp, "Permission: Read and Write\n");

    fprintf(fp2, "Operating Systems Coursework\n");
    fprintf(fp2, "This file is Read Only.\n");
    fprintf(fp2, "Permission: Read Only\n");

    fclose(fp);
    fclose(fp2);

    printf("File created successfully.\n");

    writeLog("File Created");
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

    writeLog("File Written");
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

    writeLog("File Read");

    fclose(fp);
}

void deleteFile()
{
    if(remove("sample.txt") == 0)
    {
        printf("File deleted successfully.\n");
        writeLog("File Deleted");
    }
    else
    {
        printf("Unable to delete file.\n");
    }
    
}

int login()
{
    char username[20];
    char password[20];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if(strcmp(username, "rojisha") == 0 &&
       strcmp(password, "12345") == 0)
    {
        printf("\nLogin Successful.\n");
        return 1;
    }

    printf("Invalid Username or Password.\n");

    printf("\nMaximum login attempts exceeded.\n");

    return 0;
}

void showPermission()
{
    int file;

    printf("\n1. sample.txt\n");
    printf("2. readonly.txt\n");
    printf("Choose File: ");
    scanf("%d", &file);

    if(file == 1)
        printf("sample.txt Permission : %s\n", samplePermission);
    else if(file == 2)
        printf("readonly.txt Permission : %s\n", readOnlyPermission);
    else
        printf("Invalid Choice.\n");
}

void changePermission(){
    printf("\nEnter new permission (eg: rwx, rw-, r--): ");
    int file;

    printf("\n1. sample.txt\n");
    printf("2. readonly.txt\n");
    printf("Choose File: ");
    scanf("%d", &file);

    if(file == 1)
    {
    	printf("Enter Permission: ");
    	scanf("%s", samplePermission);
    }
    else if(file == 2)
    {
    	printf("Enter Permission: ");
    	scanf("%s", readOnlyPermission);
    }
    else
    {
    	printf("Invalid Choice.\n");
    }
    printf("Permission changed successfully.\n");
}
void checkReadPermission()
{
    int file;
    char *p;

    printf("\n1. sample.txt\n");
    printf("2. readonly.txt\n");
    printf("Choose File: ");
    scanf("%d",&file);

    if(file == 1)
        p = samplePermission;
    else
        p = readOnlyPermission;

    if(p[0] == 'r')
        printf("Read Permission Granted.\n");
    else
        printf("Read Permission Denied.\n");
}


void checkWritePermission()
{
    int file;
char *p;

    printf("\n1. sample.txt\n");
    printf("2. readonly.txt\n");
    printf("Choose File: ");
    scanf("%d",&file);

    if(file == 1)
        p = samplePermission;
    else
        p = readOnlyPermission;

    if(p[1] == 'w')
        printf("Write Permission Granted.\n");
    else
        printf("Write Permission Denied.\n");
}


void checkExecutePermission()
{
    int file;
    char *p;

    printf("\n1. sample.txt\n");
    printf("2. readonly.txt\n");
    printf("Choose File: ");
    scanf("%d",&file);

    if(file == 1)
        p = samplePermission;
    else
        p = readOnlyPermission;

    if(p[2] == 'x')
        printf("Execute Permission Granted.\n");

    else
        printf("Execute Permission Denied.\n");
}

void encryptFile()
{
    FILE *fp = fopen("sample.txt", "r");
    FILE *temp = fopen("encrypted.txt", "w");

    char ch;

    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        fputc(ch + 3, temp);
    }

    fclose(fp);
    fclose(temp);

    printf("File encrypted successfully.\n");

    writeLog("File Encrypted");
}

void decryptFile()
{
    FILE *fp = fopen("encrypted.txt", "r");
    FILE *temp = fopen("decrypted.txt", "w");

    char ch;

    if(fp == NULL)
    {
        printf("Encrypted file not found.\n");
        return;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        fputc(ch - 3, temp);
    }
    

    fclose(fp);
    fclose(temp);

    printf("File decrypted successfully.\n");

    writeLog("File Decrypted");
}


void viewLog()
{
    FILE *log = fopen("audit.log","r");

    char ch;

    if(log==NULL)
    {
        printf("No audit log found.\n");
        return;
    }

    printf("\n===== Audit Log =====\n\n");

    while((ch=fgetc(log))!=EOF)
    {
        printf("%c",ch);
    }

    fclose(log);
}

int main()
{
    if(!login())
    {
        return 0;
    }

    printf("\nWelcome to the Secure File Management System\n");
    int choice;
    do
    {
        printf("\nSeccure File Management System \n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Show File Permission\n");
        printf("6. Change File Permission\n");
        printf("7. Check Read Permission\n");
        printf("8. Check Write Permission\n");
        printf("9. Check Execute Permission\n");
        printf("10. Encrypt File\n");
        printf("11. Decrypt File\n");
        printf("12. View Audit Log\n");
        printf("13. Exit\n");

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

            case 10:
                encryptFile();
                break;

            case 11:
                decryptFile();
                break;

            case 12:
    		viewLog();
    		break;

            case 13:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice!=13);

    return 0;
}
