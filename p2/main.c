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
double sumBusinessWait=0; 
int BCustomers =0; 
int ECustomers =0; 
double sumEconomyWait =0; 

static struct timeval start_time; // simulation start time

customerQueue businessQ;
customerQueue economyQ; 

 



//Make a time calc mutex here
pthread_mutex_t timeMutex; 
pthread_mutex_t businessStats; 
pthread_mutex_t econStats;
pthread_mutex_t queue; 
pthread_cond_t condQueue; 
pthread_mutex_t globalNumbers; 






// customer * makeCustomer(int id, int business, int arrivalTime, int serviceTime){
//     printf("making customer\n"); 
//     customer * newCustomer = malloc(sizeof(customer));
//      if (newCustomer == NULL) {
//         printf("Memory allocation failed\n");
//         return NULL;  // Handle memory allocation failure
//     }else{
//         printf("sucessfully allocated space for new customer\n"); 
//     }
//     newCustomer-> id = id; 
//     printf("made the id\n"); 
//     newCustomer -> business = business; 
//         printf("made the business\n"); 
//     newCustomer -> serviceTime = serviceTime; 
//             printf("made the service time\n"); 

//     newCustomer -> arrivalTime= arrivalTime; 
//         printf("made the arrival time\n"); 
//    // printf("whyyyyyyyyy\n");

  
//     printf("finished making new customer\n"); 
//   //  printf("nooooooooo\n"); 
//     return newCustomer; 
// }


//MUST IMPLEMENT!!!!!!
void sortCustomers(customer* arrayToSort, customer * rawArray, int N){
    //customer sortedArray[sizeof(arrayToSort)/sizeof(customer)]; 
    
}
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

void *clerk(){//NEED TO PASS IT THE ID OF THE CLERK. 
    pthread_mutex_lock(&globalNumbers);
    int i =0; 
    while(customersToProcess !=0){//might need a mutex on this
        printf("starting search %d\n", i); 
    pthread_mutex_unlock(&globalNumbers); 
    pthread_mutex_lock(&queue); 
        customer current; 
        int found =0; 
       // pthread_mutex_lock(&businessStats); 
        if(businessQ.quantity >=1){
             current = *pop(&businessQ); 
             found =1; 
        }else if (economyQ.quantity >=1){
             current = *pop(&economyQ); 
             found =1;
        } else{
            printf("there are no customers to help, taking a tap till they get here zzzzz\n"); 
    pthread_cond_wait(&condQueue, &queue);
        }
    pthread_mutex_unlock(&queue); 
        if(found){
        pthread_mutex_lock(&globalNumbers); 
            customersToProcess --; 
        pthread_mutex_unlock(&globalNumbers); 
            float start = getCurrentSimulationTime(); 
            printf("processing customer %d, starting at time %f, expected service time %.2f seconds\n", current.id, start, current.serviceTime/10); 
            usleep(current.serviceTime*100000);
            float end = getCurrentSimulationTime(); 
            printf("Clerk finished with customer %d, started at  %.2f and finished at %.2f\n", current.id, start, end); 

        }



        //pthread_mutex_lock(&globalNumbers);
        i ++; 
    }
    printf("DONE CLERK FUNTION\n"); 
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


int loadCustomers(FILE * inputfile, customer ** EndArray){//don't forget to check for invalid times 
    int N = 0; 
    int c =0; 
   // customer rawCust[N];
    char line[20];
    fgets(line, 20 , inputfile); //can also use stdin instead of open_file
    N = atoi(line); 
    customersToProcess =N; 
    printf("N is %d\n", N); 

    while( fgets(line, 20, inputfile)!=NULL){
        char cID[20]; 
        int IdIdx=0;  
        int business =0; 
        char cArrival[20]; 
        int IdxA =0;
        char cServiceTime[20]; 
        int IdxS =0; 
        printf("line is [%s]\n", line ); 
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
               // printf("new character of arrival time is %c\n", cArrival[IdxA]); 
                IdxA ++; 
                i ++; 
            }
            cArrival[IdxA] = '\0'; 
            i ++;
            while(line[i] != '\0' && line[i] != '\n'){
                cServiceTime[IdxS]= line[i]; 
                IdxS ++; 
                i ++; 
            }
            cServiceTime[IdxS] = '\0'; 


            
        //}
        int id = atoi(cID); 
        int arrivalTime = (float)atoi(cArrival);
        int serviceTime = (float)atoi(cServiceTime);
    // int id, business, arrivalTime, serviceTime;
    //  fscanf(inputfile, "%d %d %d %d", &id, &business, &arrivalTime, &serviceTime);
        
       // printf("int id is %d, business is %d, arrival time is %d,  service time is %d,\n", id, business, arrivalTime, serviceTime);
        //id = StringToInt(cID); 
        //arrivalTime = StringToInt(cArrival); 
        //serviceTime = StringToInt(cServiceTime); 
      //  printf("about to make customer %d\n", c);

//////MUST ADD CONDITION CHECKING!!!

        EndArray[c] = makeCustomer(id, business,  arrivalTime, serviceTime);
        if (EndArray[c] == NULL) {
            printf("Failed to create customer %d\n",c);
        }
       // printf("made customer %d\n", c); 
       printf("Just loaded customer with "); 
        printCust(EndArray[c]); 
        c ++; 
    }

    //for()
    //sortCustomers(EndArray, rawCust, N);
    return N; 
}

void dispacher(){
//void *dispatcher(void * voidArray){
//void dispatcher(customer * rawQueue[]){
    //customer * rawQueue[50] = (customer **)voidArray;

    //customer ** rawQueue = (customer **)voidArray; 
    //rawQueue++; 
    int N = customersToProcess; 
    printf("starting dispatch, there are %d customers\n", N); 
    int i = 0; 
    while(N-i>0){
        printf("getting time mutex, there are %d customers left in the array, current time is %.2f\n", N-i, getCurrentSimulationTime()); 
        pthread_mutex_lock(&timeMutex);
        printf("got time mutex\n"); 

       // printf("get current simulation time is %f\n", getCurrentSimulationTime()); 
        if(getCurrentSimulationTime()>=rawQueue[i]->arrivalTime/10){
            printf("Found a customer %d who is ready \n", rawQueue[i]->id); 
            // pthread_mutex_lock(&businessStats);
            // printf("Got business Stats mutex\n"); 

            if(rawQueue[i]-> business){
                pthread_mutex_lock(&businessStats);
                push(rawQueue[i], &businessQ); 
                printf("Customer %d entered the business queue, the current length is %d\n", rawQueue[i]->id, businessQ.quantity);
                pthread_mutex_unlock(&businessStats);
                pthread_cond_signal(&condQueue);
                i++;
                                printf("finished signaling that a customer was added\n"); 

            }else{
                pthread_mutex_lock(&econStats);
                push(rawQueue[i], &economyQ); 
                printf("Customer %d entered the economy queue, the current length is %d\n", rawQueue[i]->id, economyQ.quantity);
                pthread_mutex_unlock(&econStats);
                pthread_cond_signal(&condQueue);
                printf("finished signaling that a customer was added\n"); 
                i++;
            }
                        pthread_mutex_unlock(&timeMutex);

        }else{
            printf("there are no customers ready to enter the queue yet, "); 
            printf("The next customer will arrive in %f seconds and is ", (rawQueue[i]->arrivalTime-getCurrentSimulationTime())/10);
            printCust(rawQueue[i]); 
            pthread_mutex_unlock(&timeMutex);
            usleep(5000); 
        }
        
    }
    printf("\n\nThere are no more customers to process\n\n\n"); 
    //return NULL; 
}

int main(int argc, char ** argv){
    double sumBusinessWait=0; 
    double sumEconomyWait =0; 
    pthread_t threadArray[5]; 
    pthread_t dispatcherThread; 
    economyQ.quantity = 0; 
    businessQ.quantity = 0;  
    pthread_cond_init(&condQueue, NULL); 
    pthread_mutex_init(&queue, NULL); 
        pthread_mutex_init(&timeMutex, NULL); 
    

    
    

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
    int N = loadCustomers(inputfile, ArrayOfCust); 
  int rc; 

    for(int i =0; i < 1; i ++){
        if ((rc = pthread_create(&threadArray[i], NULL, clerk, NULL))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
    }
    if ((rc = pthread_create(&dispatcherThread, NULL, dispatcher, (void *) ArrayOfCust ))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}


    gettimeofday(&start_time, NULL); // record simulation start time
    //dispatcher(ArrayOfCust);
   // clerk();




//~~~~~~~~~~~~~~~~~~~~~~~~~~~ clean up 
    fclose(inputfile); 
      //~~~~~~~~~~~~~~ REMOVE WHEN DONE DEBUGGING!!
    for (int i =0; i < N; i ++){
        //printCust(ArrayOfCust[i]); 
        free(ArrayOfCust[i]); 
    }

    for (int i = 0; i < 1; ++i) {
		pthread_join(threadArray[i], NULL);
	}
    		pthread_join(dispatcherThread, NULL);


    printf("The average waiting time for all customers in the system is: %.2f seconds. \n", (sumBusinessWait+sumEconomyWait)/N);
    if(BCustomers !=0){
    printf("The average waiting time for Business customers in the system is: %.2f seconds. \n", (sumBusinessWait)/BCustomers);
    } else{
        printf("There were no Business customers\n"); 
    }

    if(ECustomers !=0){
    printf("The average waiting time for Economy customers in the system is: %.2f seconds. \n", (sumEconomyWait)/ECustomers);
    } else{
        printf("There were no Economy customers\n"); 
    }
    pthread_cond_destroy(&condQueue); 
    pthread_mutex_destroy(&queue); 
        pthread_mutex_destroy(&timeMutex); 

}