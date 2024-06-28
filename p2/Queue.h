#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h> 
#include <unistd.h>
#include <errno.h>

typedef struct customer{
	int id;
	int arrivalTime;
	int serviceTime; //e.g., service time
    struct customer *next; 
}customer;

customer * pop(); 

customer * peek(); 

void push(customer * cust);

