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

customer  * tail = NULL; //points to the last node,
customer * head = NULL; 
int quantity =0; 

customer * pop(){
    customer * top = head; 
    head = head -> next; 
    quantity --; 
    return top; 
}

customer * peek(){
    customer * top = head; 
    return top; 
}

void push(customer * cust){
    if(head == NULL){
       head = cust; 
        tail = cust; 
    } else{
        tail->next = cust; 
        tail = cust;
    }
    quantity ++; 

}

customer * makeCustomer(int id, int business, int arrivalTime, int serviceTime){
    printf("making customer\n"); 
    customer * newCustomer = malloc(sizeof(customer));
     if (newCustomer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;  // Handle memory allocation failure
    }else{
        printf("sucessfully allocated space for new customer\n"); 
    }
    newCustomer-> id = id; 
    printf("made the id\n"); 
    newCustomer -> business = business; 
        printf("made the business\n"); 
  newCustomer -> serviceTime = serviceTime; 
            printf("made the service time\n"); 

    newCustomer -> arrivalTime= arrivalTime; 
        printf("made the arrival time\n"); 
   // printf("whyyyyyyyyy\n");

  
    printf("finished making new customer\n"); 
  //  printf("nooooooooo\n"); 
    return newCustomer; 
}