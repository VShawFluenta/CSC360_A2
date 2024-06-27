//Queue to hold customers, by Victoria Shaw
#include <stddef.h>
#include <stdio.h> 
typedef struct _customer{
	int id;
	int arrivalTime;
	int serviceTime; //e.g., service time
    struct _customer *next; 
}customer;

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