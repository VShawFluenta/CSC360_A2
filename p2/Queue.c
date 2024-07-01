//Queue to hold customers, by Victoria Shaw
#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h>
#include "Queue.h"

// typedef struct customer{
// 	int id;
// 	int arrivalTime;
// 	int serviceTime; //e.g., service time
//     struct customer *next; 
// }customer;



customer  pop(customerQueue * Q ){
    customer top = Q->queueArray[Q->head]; 
    Q->head ++; 
    Q->quantity --; 
    return top; 
}

customer  peek(customerQueue* Q){
    customer top = Q->queueArray[Q->head]; 
    return top; 
}

void push(customer *cust, customerQueue * Q){
//        printf("the starting quantity is %d\n", Q->quantity); 

    if(Q->quantity==0){
       Q->head =0; 
       Q->tail=0; 
       Q->queueArray[0] = *cust; 
        // printf("queue was empty\n"); 
    } else{
       Q->tail++; 
       Q->tail %=50; 
        Q->queueArray[Q->tail] = *cust;

    }
    Q->quantity ++; 
        // printf("pushing customer %i, Arrival time is %.4f, and service time is %.4f\n", Q->queueArray[Q->tail].id, Q->queueArray[Q->tail].arrivalTime, Q->queueArray[Q->tail].serviceTime); 

   // printf("the current quantity is %d\n", Q->quantity); 

}
customer * makeCustomer(int id, int business, int arrivalTime, int serviceTime){
   // printf("making customer\n"); 
    customer * newCustomer = malloc(sizeof(customer));
     if (newCustomer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;  // Handle memory allocation failure
    }else{
     //   printf("sucessfully allocated space for new customer\n"); 
    }
    newCustomer-> id = id; 
   // printf("made the id\n"); 
    newCustomer -> business = business; 
   //     printf("made the business\n"); 
    newCustomer -> serviceTime = serviceTime; 
    //        printf("made the service time\n"); 

    newCustomer -> arrivalTime= arrivalTime; 
    //    printf("made the arrival time\n"); 
   // printf("whyyyyyyyyy\n");

  
    //printf("finished making new customer\n"); 
  //  printf("nooooooooo\n"); 
    return newCustomer; 
}