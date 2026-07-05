#include <stdio.h>
#include <pthread.h>

int balance = 1000;
pthread_mutex_t lock;

void *depositThread(void * arg)
{
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&lock);
        balance == 100;
        printf("Deposit Thread: Balance = %d\n", balance);
        pthread_mutex_unlock(&lock); 
 
    }
    return NULL;
}


void *withdrawThread(void *arg){
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&lock);
        balance -= 50;

        printf("Withdraw Thread: Balance = %d\n", balance); 
        pthread_mutex_unlock(&lock); 
    }
    return NULL;
}

void *balanceThread(void *arg){
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&lock);
 
        printf("Balance Thread: Current Balance = %d\n", balance) ;
        pthread_mutex_unlock(&lock); 
    }
     return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    pthread_mutex_init(&lock, NULL);
    
    printf("Initial Balance = %d\n\n", balance);
    
    pthread_create(&t1, NULL, depositThread, NULL);
    pthread_create(&t2, NULL, depositThread, NULL);
    pthread_create(&t3, NULL, depositThread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n Final Balance = %d\n", balance);
    pthread_mutex_destroy(&lock); 

    return 0;
}
