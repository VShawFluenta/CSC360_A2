//Victoria Shaw
//V01020304 Assignment 2
//CSC 360
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h> 
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "Queue.h"

int customersToProcess =0; 

void sortCustomers(customer* arrayToSort, customer * rawArray, int N){
    //customer sortedArray[sizeof(arrayToSort)/sizeof(customer)]; 
    
}

void clerk(){
    while(customersToProcess !=0){//might need a mutex on this


    }
}
int StringToInt(char * line){
    int result =0; 
    int power = strlen(line)-1;
    for(int i =0; power>=0; power--, i++){
        int a = line[i]-48;
        printf("a is %d\n", a); 
        for(int j =0; j <power; j ++){
            a*=10;
        }
        result+=a;
    }
    return result; 

}
void loadCustomers(FILE * inputfile, customer * EndArray){//don't forget to check for invalid times 
    int N = 0; 
    customer rawCust[N];
    char line[20];
    fgets(line, 20 , inputfile); //can also use stdin instead of open_file
    N = StringToInt(line); 
    printf("N is %d\n", N); 
    //for()
    //sortCustomers(EndArray, rawCust, N);
}

int main(int argc, char ** argv){
    double sumBusinessWait=0; 
    double sumEconomyWait =0; 
    pthread_t threadArray[5]; 
    
    int rc; 

    // for(int i =0; i < 5; i ++){
    //     if ((rc = pthread_create(&threadArray[i], NULL, clerk, ))) {
	// 		fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
	// 		return EXIT_FAILURE;
	// 	}
    // }

    //~~~~~~~~~~~~~~~~~~~~~~~ read from file: 
    char fname[128];
    strcpy(fname, argv[1]);
    printf("amount of entries is %d\n", argc);
    //printf("Enter .txt file name\n");
    //scanf("%123s",fname);
    FILE *inputfile;
    inputfile=fopen(fname,"r");
    if(inputfile == NULL){
        printf("file %s failed to open\n", fname); 
        return 1; 
    }else{
        printf("opened file\n"); 
    }
    customer ArrayOfCust[50];
    loadCustomers(inputfile, ArrayOfCust); 



//~~~~~~~~~~~~~~~~~~~~~~~~~~~ clean up 
    fclose(inputfile); 

    // for (int i = 0; i < 5; ++i) {
	// 	pthread_join(threadArray[i], NULL);
	// }

}