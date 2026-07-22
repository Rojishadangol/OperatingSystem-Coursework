/*
    Task 3
    Banking Management System
    Secure File Management
*/

#include <stdio.h>
#include <string.h>

char permission[]="rw-";

void logActivity(char action[])
{
    FILE *fp=fopen("audit.log","a");

    if(fp!=NULL)
    {
        fprintf(fp,"%s\n",action);
        fclose(fp);
    }
}

int login()
{
    char user[20],pass[20];

    printf("\n Bank Login \n");

    printf("Username : ");
    scanf("%s",user);

    printf("Password : ");
    scanf("%s",pass);

    if(strcmp(user,"rojisha")==0 &&
       strcmp(pass,"12345")==0)
    {
        printf("\nLogin Successful.\n");
        return 1;
    }

    printf("\nInvalid Login.\n");
    return 0;
}

void createFile()
{
    FILE *fp=fopen("customer_accounts.txt","w");

    if(fp==NULL)
        return;

    fprintf(fp,"Customer Name : Ram Sharma\n");
    fprintf(fp,"Account No    : 10001\n");
    fprintf(fp,"Balance       : Rs.50000\n");

    fclose(fp);

    printf("Customer file created.\n");

    logActivity("Customer File Created");
}

void readFile()
{
    FILE *fp=fopen("customer_accounts.txt","r");

    char ch;

    if(fp==NULL)
    {
        printf("File not found.\n");
        return;
    }

    while((ch=fgetc(fp))!=EOF)
        printf("%c",ch);

    fclose(fp);

    logActivity("Customer File Read");
}

void writeFile()
{
    FILE *fp=fopen("customer_accounts.txt","a");

    if(fp==NULL)
        return;

    fprintf(fp,"\nLast Transaction : Deposit Rs.5000\n");

    fclose(fp);

    printf("Transaction saved.\n");

    logActivity("Customer File Updated");
}

void deleteFile()
{
    remove("customer_accounts.txt");

    printf("Customer file deleted.\n");

    logActivity("Customer File Deleted");
}

void showPermission()
{
    printf("Current Permission : %s\n",permission);
}

void changePermission()
{
    printf("Enter Permission : ");
    scanf("%s",permission);
}

void encryptFile()
{
    FILE *in = fopen("customer_accounts.txt","r");

    if(in == NULL)
    {
        printf("Customer file not found.\n");
        return;
    }

    FILE *out = fopen("encrypted.txt","w");

    char ch;

    while((ch = fgetc(in)) != EOF)
    {
        fputc(ch + 3, out);
    }

    fclose(in);
    fclose(out);

    printf("Customer file encrypted successfully.\n");

    logActivity("Customer File Encrypted");
}

void decryptFile()
{
    FILE *in = fopen("encrypted.txt","r");

    if(in == NULL)
    {
        printf("Encrypted file not found.\n");
        return;
    }

    FILE *out = fopen("decrypted.txt","w");

    char ch;

    while((ch = fgetc(in)) != EOF)
    {
        fputc(ch - 3, out);
    }

    fclose(in);
    fclose(out);

    printf("Customer file decrypted successfully.\n");

    logActivity("Customer File Decrypted");
}

void readPolicy()
{
    FILE *fp = fopen("bank_policy.txt","r");

    if(fp == NULL)
    {
        printf("Policy file not found.\n");
        return;
    }

    char ch;

    printf("\n Bank Policy \n");

    while((ch=fgetc(fp))!=EOF)
        printf("%c",ch);

    fclose(fp);
}
void viewLog()
{
    FILE *fp=fopen("audit.log","r");

    char ch;

    if(fp==NULL)
        return;

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
        
        printf(" Secure Banking File System\n");
      
        printf("1.Create Customer File\n");
        printf("2.Update Customer File\n");
        printf("3.Read Customer File\n");
        printf("4.Delete Customer File\n");
        printf("5.Show Permission\n");
        printf("6.Change Permission\n");
        printf("7.Encrypt File\n");
        printf("8.Decrypt File\n");
        printf("9.View Audit Log\n");
        printf("10.Read Bank Policy\n");
        printf("11.Exit\n");

        printf("Choice : ");
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
    		readPolicy();
    		break;
            case 11:
		printf("Program Ended.\n");
		break;
            default:printf("Invalid Choice.\n");
        }

    }while(choice!=11);

    return 0;
}
