#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h> 
#include <unistd.h>
#include <errno.h>

typedef struct customer{
	int id;
	int business; 
	float arrivalTime;
	float serviceTime; 
	float waitTime; 
    struct customer *next; 
}customer;

typedef struct customerQueue{
	customer * head; 
	customer * tail; 
	int quantity; 
}customerQueue;

customer * pop(customerQueue* Q); 

customer * peek(customerQueue* Q); 

void push(customer * cust, customerQueue* Q);

customer * makeCustomer(int id, int business, int arrivalTime, int serviceTime); 

