/* For printf() */
#include <stdio.h>

/* For fork() */
#include <unistd.h>

/* For SIGINT */
#include <signal.h>

/* For the ok signal */
#define SIGOK 10

void foo(int sig);
void F(void);
void createProcess (void (*F) (void));
int sendSignal();

void foo(int sig) {
	if(pause() == SIGINT) {
		createProcess(F);
	}
	if(pause() == SIGOK) {
		sexndSignal();
	}
}

void F(void) {
	printf("hey");
	fflush(stdout);
	foo(0);
	signal(SIGOK, foo);
}

void createProcess (void (*F) (void)) {
	if (!fork()) { //Here the child is running.
		F();
	}
}

int sendSignal(int sig) {
	signal(SIGINT, foo);
	if (pause() == SIGOK) {
		printf("hoy");
		fflush(stdout);
	}
}

int main() {
	createProcess(F);
	return 0;
}
