/* For printf() */
#include <stdio.h>

/* For fork() */
#include <unistd.h>

/* For the type pid_t */
#include <sys/types.h>

/* For the wait function */
#include <sys/wait.h>

/* The main function */
int main(void) {

	int j = 0; // This value will be initiate in the wait function.
	int i = 0; // The number of children.

	/* From here we're creating the tree of processes */
	// Use of the function fork : two things in the same time : create a new process and if the return value is 0, then the child is running, if the return is 1, the father is running.
	if(fork()) { // Here the father is running.
        	if(fork()) {
            		if(!fork()) //Here the child is running.
                		fork();
        	}
    	}
	else {
        	if(fork()) {
            		if(fork()) {
                		if(!fork()) 
                    			fork();
            		}
        	}
		else {
           		if(fork()) {
                		if(!fork()) {
                   			if(!fork())
                        			fork();
                		}
            		}
			else {
                		fork();
            		}
        	}
    	}
	/* To here */

    	while(wait(&j)>=0) // The wait function is an observable for the child process. Which means that since a child finish to run the father is notified. 
		// Also, the function wait is receive as an argument the return of the main of the child process.
        	i=i+j/256+1; // The value j is not the number of children of the children * 256. 
    	printf("i'm the process : %d, and i have %d children. \n",getpid(), i); // Print first the process id, then the number of children.
    	return i; // Return the number of children that the process have, and this value is multiplicate by 256, and then sended to the wait of the father (if he exists).
}
