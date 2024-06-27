//Victoria Shaw
//V01020304 Assignment 2
//CSC 360
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h> 
#include <unistd.h>
#include <errno.h>
#include <Queue.h> 

int customersToProcess =0; 


void clerk(){
    while(customersToProcess !=0){//might need a mutex on this

    }
}
void loadCustomers(){//don't forget to check for invalid times 
}

int main(){
    double sumBusinessWait=0; 
    double sumEconomyWait =0; 
    pthread_t threadArray[5]; 
    int rc; 

    for(int i =0; i < 5; i ++){
        if ((rc = pthread_create(&threadArray[i], NULL, clerk, ))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
    }

    for (int i = 0; i < 5; ++i) {
		pthread_join(threadArray[i], NULL);
	}

}