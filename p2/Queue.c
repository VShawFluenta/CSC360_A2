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



customer * pop(customerQueue Q){
    customer * top = Q.head; 
    Q.head = Q.head -> next; 
    Q.quantity --; 
    return top; 
}

customer * peek(customerQueue Q){
    customer * top = Q.head; 
    return top; 
}

void push(customer * cust, customerQueue Q){
        printf("the starting quantity is %d\n", Q.quantity); 

    printf("pushing customer %i\n", cust-> id); 
    if(Q.head == NULL){
       Q.head = cust; 
        Q.tail = cust; 
        printf("queue was empty\n"); 
    } else{
        Q.tail->next = cust; 
        Q.tail = cust;
    }
    Q.quantity ++; 
    printf("the current quantity is %d\n", Q.quantity); 

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