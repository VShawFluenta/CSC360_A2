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
#include <stdlib.h>
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
int StringToInt(char * line){//NOT NEEDED ANYMORE!!
    int result =0; 
    int power = strlen(line)-1;
        printf("In convert String to Int and the word is %s and its length is %d\n", line, power+1);

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

void printCust(customer * cust){
    printf("About to try and print a customer\n"); 
    if(cust ==NULL){
        printf("cust is NULL, can't print it\n"); 
    }else {
        printf("Yay, you found a valid customer\n"); 
    }
    printf("id is %d", cust->id); 
    if(cust->business){
        printf(" and this customer is in business\n"); 
    } else {
        printf(" and this customer is in economy class\n"); 
    }
}
void loadCustomers(FILE * inputfile, customer ** EndArray){//don't forget to check for invalid times 
    int N = 0; 
    int c =0; 
    customer rawCust[N];
    char line[20];
    fgets(line, 20 , inputfile); //can also use stdin instead of open_file
    N = atoi(line); 
    customersToProcess =N; 
    printf("N is %d\n", N); 

    for(c =0; c<N; c ++){

    // while( fgets(line, 20, inputfile)!=NULL){
    //     char cID[20]; 
    //     int IdIdx=0;  
    //     int business =0; 
    //     char cArrival[20]; 
    //     int IdxA =0;
    //     char cServiceTime[20]; 
    //     int IdxS =0; 
    //     printf("line is [%s]\n", line ); 
    //     //for(int i =0; i < 20; i++){
    //     int i =0; 
    //         while(line[i] != ':'){
    //             cID[IdIdx]= line[i]; 
    //             IdIdx ++;
    //             i ++; 
    //         }
    //         cID[IdIdx]='\0'; 
    //        // printf("Id is %s\n", cID);
    //         business = line[i++]-48; 
    //         while(line[i] != ','){
    //             cArrival[IdxA]= line[i]; 
    //             IdxA ++; 
    //             i ++; 
    //         }
    //         cServiceTime[IdxA] = '\0'; 
    //         i ++;
    //         while(line[i] != ','){
    //             cServiceTime[IdxS]= line[i]; 
    //             IdxS ++; 
    //             i ++; 
    //         }
    //         cServiceTime[IdxS] = '\0'; 


            
    //     //}
    //     int id = atoi(cID); 
    //     int arrivalTime = atoi(cArrival);
    //     int serviceTime = atoi(cServiceTime);
    int id, business, arrivalTime, serviceTime;
        fscanf(inputfile, "%d %d %d %d", &id, &business, &arrivalTime, &serviceTime);
        
    printf("int id is %d, business is %d, service time is %d, and arrival time is %d\n", id, business,serviceTime, arrivalTime);
        //id = StringToInt(cID); 
        //arrivalTime = StringToInt(cArrival); 
        //serviceTime = StringToInt(cServiceTime); 
        printf("about to make customer %d\n", c);
        EndArray[c] = makeCustomer(id, business,  arrivalTime, serviceTime);
        if (EndArray[c] == NULL) {
            printf("Failed to create customer %d\n",c);
        }
        printf("made customer %d\n", c); 
        printCust(EndArray[c]); 
        c ++; 
    }

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
   // printf("amount of entries is %d\n", argc);
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
    customer * ArrayOfCust[50];
     loadCustomers(inputfile, ArrayOfCust); 
    for (int i =0; i < customersToProcess; i ++){
        printCust(ArrayOfCust[i]); 
        free(ArrayOfCust[i]); 
    }



//~~~~~~~~~~~~~~~~~~~~~~~~~~~ clean up 
    fclose(inputfile); 

    // for (int i = 0; i < 5; ++i) {
	// 	pthread_join(threadArray[i], NULL);
	// }

}