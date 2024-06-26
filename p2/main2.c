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

//These are here as a reminder, they are properly declared in the .h file. 
// typedef struct customer{
// 	int id;
// 	int business; 
// 	float arrivalTime;
// 	float serviceTime; 
// 	float waitTime; 
//    // struct customer *next; 
// }customer;

// typedef struct customerQueue{
// 	int head; 
// 	int tail; 
// 	int quantity; 
//     customer queueArray[50]; 
// }customerQueue;

int customersToProcess =0; //Customers remaining in the queues or in the array to be put into the queues
double sumBusinessWait=0; //Sum of all the wait times, 
int BCustomers =0; //number of business and econ customers respectively 
int ECustomers =0; 
double sumEconomyWait =0; 
customer * ArrayOfCust[50];

static struct timeval start_time; // simulation start time

customerQueue businessQ;
customerQueue economyQ; 

 



//Make a time calc mutex here
// pthread_mutex_t timeMutex;  //These three are not needed. 
// pthread_mutex_t businessStats; 
// pthread_mutex_t econStats;
pthread_mutex_t queue; 
pthread_cond_t condQueue; 
pthread_mutex_t globalNumbers; 











//Used to initialize the customers in the arrays of customer pointers within each queue. -333 would not be a valid entry, so if it is printed then I know I have an error
void initArray(customerQueue *Q, int N){
    for(int i =0; i < N; i ++){
        Q->queueArray[i].arrivalTime=-333; 
        Q->queueArray[i].serviceTime=-333; 
        Q->queueArray[i].id=-333; 

    }
}

// // Merges two subarrays of arr[].
// // First subarray is arr[l..m]
// // Second subarray is arr[m+1..r]
// // Inplace Implementation
// void merge(customer * arr[], int start, int mid, int end){
// 	int start2 = mid + 1;

// 	// If the direct merge is already sorted
// 	if (arr[mid]->arrivalTime <= arr[start2]->arrivalTime) {
// 		return;
// 	}

// 	// Two pointers to maintain start
// 	// of both arrays to merge
// 	while (start <= mid && start2 <= end) {

// 		// If element 1 is in right place
// 		if (arr[start]->arrivalTime <= arr[start2]->arrivalTime ) {
// 			start++;
// 		}
// 		else {
// 			int value = arr[start2]->arrivalTime ;
// 			int index = start2;

// 			// Shift all the elements between element 1
// 			// element 2, right by 1.
// 			while (index != start) {
// 				arr[index]->arrivalTime  = arr[index - 1]->arrivalTime ;
// 				index--;
// 			}
// 			arr[start]->arrivalTime  = value;

// 			// Update all the pointers
// 			start++;
// 			mid++;
// 			start2++;
// 		}
// 	}
// }


// /* l is for left index and r is right index of the
// sub-array of arr to be sorted */
// void mergeSort(customer * arr[], int l, int r)
// {
// 	if (l < r) {

// 		// Same as (l + r) / 2, but avoids overflow
// 		// for large l and r
// 		int m = l + (r - l) / 2;

// 		// Sort first and second halves
// 		mergeSort(arr, l, m);
// 		mergeSort(arr, m + 1, r);

// 		merge(arr, l, m, r);
// 	}
// }

//MUST IMPLEMENT!!!!!! Implemented with array based merge sort. 
//Credit to Geeks for Geeks for basis of this code https://www.geeksforgeeks.org/in-place-merge-sort/
//Merge sort not used, but kept so I can tinker with it to get it working. 


void sortCustomers( int N){
//mergeSort(ArrayOfCust, 0, N);
//Very basic insertion sort of my own since merge sort isn't working
 int minStart = ArrayOfCust[0]-> arrivalTime; 
    int minIdx =0;  
for(int i =0; i < N; i ++){
   minStart = ArrayOfCust[i]->arrivalTime;
   minIdx = i; 
    for (int j =i; j < N; j ++){
        if(ArrayOfCust[j]->arrivalTime< minStart){//if found a customer that arrives before current "min" save that
            minStart = ArrayOfCust[j]-> arrivalTime; 
            minIdx =j; 
        }

    }
    //customer* min = makeCustomer(ArrayOfCust[minIdx]->id, ArrayOfCust[minIdx]->business, ArrayOfCust[minIdx]-> arrivalTime, ArrayOfCust[minIdx]->serviceTime); 
    //customer* old = makeCustomer(ArrayOfCust[i]->id, ArrayOfCust[i]->business, ArrayOfCust[i]-> arrivalTime, ArrayOfCust[i]->serviceTime); 
    // ArrayOfCust[i] = min; 
    // ArrayOfCust[minIdx] = old; 
    customer * temp = ArrayOfCust[i]; 
    ArrayOfCust[i]= ArrayOfCust[minIdx]; 
    ArrayOfCust[minIdx]= temp; 
    if(i!=minIdx){
    // printf("Swapped customer at index %d for customer at index %d\n", i, minIdx);
    }
}
}







//This function gets the current time in seconds based on a start time listed in global scope
double getCurrentSimulationTime(){
	
	struct timeval cur_time;
	double cur_secs, init_secs;
	
	//pthread_mutex_lock(&start_time_mtex); you may need a lock here
	init_secs = (start_time.tv_sec + (double) start_time.tv_usec / 1000000);
	//pthread_mutex_unlock(&start_time_mtex);
	
	gettimeofday(&cur_time, NULL);
	cur_secs = (cur_time.tv_sec + (double) cur_time.tv_usec / 1000000);
	
	return cur_secs - init_secs;
}  


//This function (run as a thread only) takes the next customer (prioritizing business)
//and "processes" them before returning back to the queues to get the next.
void *clerk(void * clerkidVoid){
long int clerkid = (long int) clerkidVoid; 
    pthread_mutex_lock(&globalNumbers);
    int i =0; 
    while(customersToProcess !=0){//might need a mutex on this
        // printf("starting search %d\n", i); 
    pthread_mutex_unlock(&globalNumbers); 
    pthread_mutex_lock(&queue); 
        customer current; 
        int found =0; 
        // pthread_mutex_lock(&businessStats); 
        // pthread_mutex_lock(&econStats);
        if(businessQ.quantity >=1){//If there are customers to service, then help them 
           // printf("There are %d customers in Business Queue\n", businessQ.quantity); 
             current = pop(&businessQ); 
             found =1; 
             BCustomers++; 
            // pthread_mutex_unlock(&businessStats);
        }else if (economyQ.quantity >=1){//If there are customers to service, then help them 
            //printf("There are %d customers in economy Queue\n", economyQ.quantity); 

             current = pop(&economyQ); 
             found =1;
             ECustomers++; 
        } else{
            printf("I am clerk %ld, there are no customers to help, taking a nap till they get here zzzzz\n", clerkid); 
    pthread_cond_wait(&condQueue, &queue);
        }
        // pthread_mutex_unlock(&econStats); 
        //      pthread_mutex_unlock(&businessStats);
    pthread_mutex_unlock(&queue); 
        if(found){
        pthread_mutex_lock(&globalNumbers); 
            customersToProcess --; 
        pthread_mutex_unlock(&globalNumbers); 
            float start = getCurrentSimulationTime(); 
            printf("I am clerk %ld and I am processing customer %d, starting at time %f(s), expected service time %.0f seconds\n",clerkid, current.id, start, current.serviceTime/10); 
            usleep(current.serviceTime*100000);//sleep for service time in seconds 
            float end = getCurrentSimulationTime(); 
            float wait = start-current.arrivalTime/10; 
            printf("Clerk %ld finished with customer %d, started at  %.2f(s) and finished at %.2f(s). Wait time was %.3f(s)\n",clerkid, current.id, start, end, wait); 
            pthread_mutex_lock(&globalNumbers); 
            if(current.business){
                sumBusinessWait += wait; 
                // printf("The new sum of business wait times is %f\n", sumBusinessWait);
            }else {
                sumEconomyWait += wait; 
                // printf("The new sum of economy wait times is %f\n", sumEconomyWait);

            }
            pthread_mutex_unlock(&globalNumbers);             
        }



        //pthread_mutex_lock(&globalNumbers);
        i ++; 
    }
    printf("I am clerk %ld and there will be no more customers today. I am done and I will wait for my co-workers to finish with their clients\n", clerkid); 
                    pthread_cond_signal(&condQueue);
                    pthread_mutex_unlock(&globalNumbers); 

    return NULL;
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
    //printf("About to try and print a customer\n");
    if(cust ==NULL){
        printf("cust is NULL, can't print it\n"); 
    }else {
     //   printf("Yay, you found a valid customer\n"); 
    }
    printf("id is %d, Arrival time is %f, service time is %f", cust->id, cust->arrivalTime, cust->serviceTime); 
    if(cust->business){
        printf(" and is in business\n"); 
    } else {
        printf(" and is in economy class\n"); 
    }
}


int loadCustomers(FILE * inputfile){//don't forget to check for invalid times 
//int loadCustomers(FILE * inputfile){//don't forget to check for invalid times 
   // int N = 0; 
    int c =0; 
   // customer rawCust[N];
    char line[20];
    fgets(line, 20 , inputfile); //can also use stdin instead of open_file
    //N = atoi(line); 
   
    // printf("N is %d\n", N); 

    while( fgets(line, 20, inputfile)!=NULL){
        char cID[20]; 
        int IdIdx=0;  
        int business =0; 
        char cArrival[20]; 
        int IdxA =0;
        char cServiceTime[20]; 
        int IdxS =0;
        int foundinvalid =0;  
        // printf("line is [%s]\n", line ); 
        //for(int i =0; i < 20; i++){
        int i =0; 
            while(line[i] != ':'){
                cID[IdIdx]= line[i]; 
                IdIdx ++;
                i ++; 
            }
            cID[IdIdx]='\0'; 
           // printf("Id is %s\n", cID);
           i++; 
            business = line[i++]-48; 
            i++;
            while(line[i] != ','){
                cArrival[IdxA]= line[i];
                // if(line[i]== '.' ||line[i]== '-') {
                //     foundinvalid ++;
                // }
               // printf("new character of arrival time is %c\n", cArrival[IdxA]); 
                IdxA ++; 
                i ++; 
            }
            cArrival[IdxA] = '\0'; 
            i ++;
            while(line[i] != '\0' && line[i] != '\n'){
                cServiceTime[IdxS]= line[i]; 
                if(line[i]== '.' || line[i]== '-' ) {
                    foundinvalid ++;
                }
                IdxS ++; 
                i ++; 
            }
            cServiceTime[IdxS] = '\0'; 


            
        //}
        int id = atoi(cID); 
        int arrivalTime = (float)atoi(cArrival);
        int serviceTime = (float)atoi(cServiceTime);
        // if(arrivalTime < 0 || serviceTime<=0){
        //     foundinvalid ++; 
        // }
    // int id, business, arrivalTime, serviceTime;
    //  fscanf(inputfile, "%d %d %d %d", &id, &business, &arrivalTime, &serviceTime);
        
       // printf("int id is %d, business is %d, arrival time is %d,  service time is %d,\n", id, business, arrivalTime, serviceTime);
        //id = StringToInt(cID); 
        //arrivalTime = StringToInt(cArrival); 
        //serviceTime = StringToInt(cServiceTime); 
      //  printf("about to make customer %d\n", c);

//////MUST ADD CONDITION CHECKING!!!
        if(foundinvalid==0){
            ArrayOfCust[c] = makeCustomer(id, business,  arrivalTime, serviceTime);
            if (ArrayOfCust[c] == NULL) {
                printf("Failed to create customer %d\n",c);
            }
                        c++;

        }else{
            printf("There was an invlid entry with %d issues\n", foundinvalid); 

        }
       // printf("made customer %d\n", c); 
    //    printf("Just loaded customer with "); 
        // printCust(ArrayOfCust[c]); 
    }

    //for()
    //sortCustomers(EndArray, rawCust, N);
    printf("done loading customers from file\n"); 
    // for(int i =0; i < N; i ++){
    //     printCust(ArrayOfCust[i]); 
    // }
     customersToProcess =c; 
    return c; 
}

void * dispatcher(){
//void *dispatcher(void * voidArray){
//void dispatcher(customer * ArrayOfCust[]){
    //customer * rawQueue[50] = (customer **)voidArray;

    //customer ** ArrayOfCust = (customer **)voidArray; 
    //rawQueue++; 
    int N = customersToProcess; 
    printf("Airline is opening, all clerks are ready, customers will now start arriving, there will be %d customers today\n", N); 
    int i = 0; 
               // printCust(ArrayOfCust[2]);

    while(i<N){
// printf("getting time mutex, there are %d customers left in the array, current time is %.2f\n", N-i, getCurrentSimulationTime()); 
              // printCust(ArrayOfCust[2]);

        // pthread_mutex_lock(&timeMutex);
       // printf("got time mutex\n"); 

       // printCust(ArrayOfCust[2]);
      //  int currentTime = getCurrentSimulationTime(); 
        // printCust(ArrayOfCust[0]); 
    //     printf("get current simulation time is %.6f\n", getCurrentSimulationTime()); 
        if(getCurrentSimulationTime()>=ArrayOfCust[i]->arrivalTime/10){
            // printf("Found a customer with id %d who is ready at index %d\n", ArrayOfCust[i]->id, i); 
            
            //pthread_mutex_lock(&businessStats);
            // printf("Got business Stats mutex\n"); 
    pthread_mutex_lock(&queue); 
            if(ArrayOfCust[i]-> business==1){
                // pthread_mutex_lock(&businessStats);
                push(ArrayOfCust[i], &businessQ); 
                printf("Customer %d entered the business queue at %f(s), the current queue length is %d\n", ArrayOfCust[i]->id,getCurrentSimulationTime(), businessQ.quantity);
                
               // pthread_mutex_unlock(&businessStats);
                pthread_cond_signal(&condQueue);
                i++;
                //printf("finished signaling that a customer was added\n"); 

            }else{
                // pthread_mutex_lock(&econStats);
                push(ArrayOfCust[i], &economyQ); 
                printf("Customer %d entered the economy queue at %f(s), the current queue length is %d\n", ArrayOfCust[i]->id, getCurrentSimulationTime(),economyQ.quantity);
                // pthread_mutex_unlock(&econStats);
                pthread_cond_signal(&condQueue);
                // printf("finished signaling that a customer was added\n"); 
                i++;
            }
       pthread_mutex_unlock(&queue);

        }else{
            // printf("there are no customers ready to enter the queue yet, "); 
        //    float remainingTime = (float)ArrayOfCust[i]->arrivalTime;
            // printf("The next customer will arrive in %f seconds and is ", (remainingTime-getCurrentSimulationTime())/10);
            
            // printCust(ArrayOfCust[i]); 
           // pthread_mutex_unlock(&timeMutex);
            // usleep(5000); //This was only so that it would take slightly longer to run and print less statements 
           // printCust(ArrayOfCust[i]); 
        }
        
    }
    printf("\n\nThere are no more customers to enter either queue\n\n\n"); 
   return NULL; 
}

int main(int argc, char ** argv){

    pthread_t threadArray[5]; //Array of clerk threads
    pthread_t dispatcherThread; //This thread releases customers to the queues when they "arrive"
    economyQ.quantity = 0; 
    businessQ.quantity = 0;  
    if(pthread_cond_init(&condQueue, NULL)!=0 ||pthread_mutex_init(&queue, NULL)!=0 ){
        printf("Error in creading condition variable or mutex, ending early\n"); //COULD USE ERRNO HERE
        return 1; 
    } 
    
        // pthread_mutex_init(&timeMutex, NULL); 
    //customer * ArrayOfCust[50];
    
    
    

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
        return EXIT_FAILURE; 
    }else{
        printf("opened file\n"); 
    }
    // customer * ArrayOfCust[50];
    int N = loadCustomers(inputfile); //Reads the files from the file and checks the validity. Does not sort
    if(N ==0){
        printf("No valid customers could be found in %s, please provide valid input\n", fname); 
        return EXIT_FAILURE; 
    }
    initArray(&businessQ, N); 
    initArray(&economyQ, N); 
    printf("Done initializing arrays\n");
    int rc; 
    sortCustomers(N); //In place sorting of the customers read from the file in case they were unordered
    gettimeofday(&start_time, NULL); // record simulation start time

    for(long int i =0; i < 5; i ++){
        if ((rc = pthread_create(&threadArray[i], NULL, clerk, (void* )i))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
    }
    if ((rc = pthread_create(&dispatcherThread, NULL, dispatcher, NULL ))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}


   // dispatcher(ArrayOfCust);
   // clerk();




//~~~~~~~~~~~~~~~~~~~~~~~~~~~ clean up 
    fclose(inputfile); 
      //~~~~~~~~~~~~~~ REMOVE WHEN DONE DEBUGGING!!
    // for (int i =0; i < N; i ++){
    //     //printCust(ArrayOfCust[i]); 
    //    // free(ArrayOfCust[i]); 
    // }

    for (int i = 0; i < 5; ++i) {
		pthread_join(threadArray[i], NULL);
	}
    		pthread_join(dispatcherThread, NULL);


    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\nThe average waiting time for all customers in the system is: %.2f seconds. \n", (sumBusinessWait+sumEconomyWait)/(float)N);
    if(BCustomers !=0){
    printf("The average waiting time for Business customers in the system is: %.2f seconds, and the total business wait time was %.2f. \n", ((sumBusinessWait)/(float)BCustomers), sumBusinessWait);
    } else{
        printf("There were no Business customers\n"); 
    }

    if(ECustomers !=0){
    printf("The average waiting time for Economy customers in the system is: %.2f seconds, and the total wait time was: %.2f\n", ((sumEconomyWait)/(float)ECustomers), sumEconomyWait);
    } else{
        printf("There were no Economy customers\n"); 
    }//||    pthread_mutex_destroy(&queue) !=0|| pthread_mutex_destroy(&globalNumbers) !=0

    if( pthread_cond_destroy(&condQueue) !=0 ){
        printf("There was an error in destroying the condition variable\n");
        perror("Error"); 
    }
    if( errno = pthread_mutex_destroy(&queue) !=0 ){
        printf("There was an error in destroying the queue mutex\n");
        perror("Error"); 
    }
   
         

}