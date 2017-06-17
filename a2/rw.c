/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "rw.h"
#include "resource.h"

/*
 * Declarations for reader-writer shared variables -- plus concurrency-control
 * variables -- must START here.
 */

sem_t key;

int reader = 0;


static resource_t data;

void initialize_readers_writer() {
    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */
	sem_init(&key,0,1);
}


void rw_read(char *value, int len) {
    printf("NOTHING IMPLEMENTED YET FOR rw_read\n");
	
	sem_wait(&key);
	reader++;
	sem_post(&key);	
	// issue read
	read_resource(&data,value,len);
	sem_wait(&key);
	reader--;
	sem_post(&key);
	
	
	
	
}


void rw_write(char *value, int len) {
    printf("NOTHING IMPLEMENTED YET FOR rw_write\n");
	
	for(;;){
		sem_wait(&key);
		if(reader == 0){
			break;
		}else{
			sem_post(&key);
		}
	}
	
	// now writer has key. no one can enter.
	// issue write
	write_resource(&data,value,len);
	sem_post(&key);
	
	
}
