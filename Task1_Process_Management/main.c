#include <stdio.h>
#include <pthread.h>

void *depositThread(void * arg)
{
    printf("Thread 1 : Deposit operation started.\n"); 
    return NULL;
}

void *withdrawThread(void *arg){
    printf("Thread 2 : Withdraw operation started.\n"); 
    return NULL;
}

void *balanceThread(void *arg){ 
    printf("Thread 3 : Checking account balance.\n") ;
    return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    
    printf("Creating threads...\n\n");
    
    pthread_create(&t1, NULL, depositThread, NULL);
    pthread_create(&t2, NULL, depositThread, NULL);
    pthread_create(&t3, NULL, depositThread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n All threads have  finished execution. \n");

    return 0;
}
