#include <stdio.h>
#include <pthread.h>

int balance = 1000;

void *depositThread(void * arg)
{
    for(int i = 0; i < 5; i++){
        balance == 100;
        printf("Deposit Thread: Balance = %d\n", balance); 
    }
    return NULL;
}


void *withdrawThread(void *arg){
    for(int i = 0; i < 5; i++){
        balance -= 50;

        printf("Withdraw Thread: Balance = %d\n", balance); 
    }
    return NULL;
}

void *balanceThread(void *arg){
    for(int i = 0; i < 5; i++){
 
        printf("Balance Thread: Current Balance = %d\n", balance) ;
    }
     return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    
    printf("Initial Balance = %d\n\n", balance);
    
    pthread_create(&t1, NULL, depositThread, NULL);
    pthread_create(&t2, NULL, depositThread, NULL);
    pthread_create(&t3, NULL, depositThread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n Final Balance = %d\n", balance);

    return 0;
}
