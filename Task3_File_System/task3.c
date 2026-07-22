/*
    Task 3
    Banking Management System
    Secure File Management
*/

#include <stdio.h>
#include <string.h>

#define NUM_USERS 3

typedef struct
{
    char username[20];
    char password[20];
    char permission[4];
}User;

User users[NUM_USERS]=
{
    {"admin","1234","rwx"},
    {"manager","2345","rw-"},
    {"teller","3456","r--"}
};

int currentUser=-1;

void logActivity(char action[])
{
    FILE *fp=fopen("audit.log","a");

    if(fp!=NULL)
    {
        fprintf(fp,"[%s] %s\n",users[currentUser].username,action);
        fclose(fp);
    }
}



int login()
{
    char user[20];
    char pass[20];

    printf("\n ABC Bank Login \n");

    printf("Username : ");
    scanf("%s",user);

    printf("Password : ");
    scanf("%s",pass);

    for(int i=0;i<NUM_USERS;i++)
    {
        if(strcmp(user,users[i].username)==0 &&
           strcmp(pass,users[i].password)==0)
        {
            currentUser=i;

            printf("\nLogin Successful.\n");
            printf("Welcome %s\n",users[i].username);
            printf("Permission : %s\n",users[i].permission);

            return 1;
        }
    }

    printf("\nInvalid Username or Password.\n");

    return 0;
}


int canRead()
{
    return users[currentUser].permission[0]=='r';
}

int canWrite()
{
    return users[currentUser].permission[1]=='w';
}

int canExecute()
{
    return users[currentUser].permission[2]=='x';
}


void createFile()
{
    if(!canWrite())
    {
        printf("Permission Denied.\n");
        logActivity("Create File Denied");
        return;
    }

    FILE *fp=fopen("customer_accounts.txt","w");

    if(fp==NULL)
    {
        printf("Unable to create file.\n");
        return;
    }

    fprintf(fp,"ABC Bank\n");
    
    fprintf(fp,"Customer : Ram Sharma\n");
    fprintf(fp,"Account  : 10001\n");
    fprintf(fp,"Balance  : Rs.50000\n");

    fclose(fp);

    printf("Customer file created successfully.\n");

    logActivity("Customer File Created");
}



void readFile()
{
    if(!canRead())
    {
        printf("Permission Denied.\n");
        logActivity("Read File Denied");
        return;
    }

    FILE *fp=fopen("customer_accounts.txt","r");

    if(fp==NULL)
    {
        printf("File not found.\n");
        return;
    }

    char ch;

    printf("\n Customer Record \n");

    while((ch=fgetc(fp))!=EOF)
        printf("%c",ch);

    fclose(fp);

    logActivity("Customer File Read");
}


void writeFile()
{
    if(!canWrite())
    {
        printf("Permission Denied.\n");
        logActivity("Update File Denied");
        return;
    }

    FILE *fp=fopen("customer_accounts.txt","a");

    if(fp==NULL)
    {
        printf("File not found.\n");
        return;
    }

    fprintf(fp,"\nLast Transaction : Deposit Rs.5000\n");

    fclose(fp);

    printf("Customer record updated.\n");

    logActivity("Customer File Updated");
}

void deleteFile()
{
    if(!canWrite())
    {
        printf("Permission Denied.\n");
        logActivity("Delete File Denied");
        return;
    }

    if(remove("customer_accounts.txt")==0)
    {
        printf("Customer file deleted successfully.\n");
        logActivity("Customer File Deleted");
    }
    else
    {
        printf("File not found.\n");
    }
}

void showPermission()
{
    printf("\nCurrent User : %s\n",users[currentUser].username);
    printf("Permission   : %s\n",users[currentUser].permission);
}

void changePermission()
{
    if(strcmp(users[currentUser].username,"admin")!=0)
    {
        printf("Only Admin can change permissions.\n");
        logActivity("Permission Change Denied");
        return;
    }

    char user[20];
    char newPermission[4];

    printf("Enter Username : ");
    scanf("%s",user);

    for(int i=0;i<NUM_USERS;i++)
    {
        if(strcmp(user,users[i].username)==0)
        {
            printf("Enter Permission (rwx/rw-/r--) : ");
            scanf("%3s",newPermission);

            if(strlen(newPermission)!=3)
            {
                printf("Invalid Permission.\n");
                return;
            }

            strcpy(users[i].permission,newPermission);

            printf("Permission Updated.\n");

            logActivity("Permission Changed");

            return;
        }
    }

    printf("User not found.\n");
}

void encryptFile()
{
    if(!canExecute())
    {
        printf("Permission Denied.\n");
        logActivity("Encrypt File Denied");
        return;
    }

    FILE *in=fopen("customer_accounts.txt","r");

    if(in==NULL)
    {
        printf("Customer file not found.\n");
        return;
    }

    FILE *out=fopen("encrypted.txt","w");

    char ch;

    while((ch=fgetc(in))!=EOF)
        fputc(ch+3,out);

    fclose(in);
    fclose(out);

    printf("Customer file encrypted successfully.\n");

    logActivity("Customer File Encrypted");
}

void decryptFile()
{
    if(!canExecute())
    {
        printf("Permission Denied.\n");
        logActivity("Decrypt File Denied");
        return;
    }

    FILE *in=fopen("encrypted.txt","r");

    if(in==NULL)
    {
        printf("Encrypted file not found.\n");
        return;
    }

    FILE *out=fopen("decrypted.txt","w");

    char ch;

    while((ch=fgetc(in))!=EOF)
        fputc(ch-3,out);

    fclose(in);
    fclose(out);

    printf("Customer file decrypted successfully.\n");

    logActivity("Customer File Decrypted");
}

void viewLog()
{
    FILE *fp=fopen("audit.log","r");

    if(fp==NULL)
    {
        printf("Audit log not found.\n");
        return;
    }

    char ch;

    printf("\n Audit Log \n");

    while((ch=fgetc(fp))!=EOF)
        printf("%c",ch);

    fclose(fp);
}

int main()
{
    int choice;

    if(!login())
        return 0;

    do
    {
        
        printf("   ABC Bank File Management System\n");
        
        printf("Logged in as : %s\n", users[currentUser].username);
        printf("\n");
        printf("1. Create Customer File\n");
        printf("2. Update Customer File\n");
        printf("3. Read Customer File\n");
        printf("4. Delete Customer File\n");
        printf("5. Show Permission\n");
        printf("6. Change Permission\n");
        printf("7. Encrypt File\n");
        printf("8. Decrypt File\n");
        printf("9. View Audit Log\n");
        printf("10. Exit\n");

        printf("\nEnter Choice : ");
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
                encryptFile();
                break;

            case 8:
                decryptFile();
                break;

            case 9:
                viewLog();
                break;

            case 10:
                printf("\nThank you for using ABC Bank File Management System.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    }while(choice != 10);

    return 0;
}
