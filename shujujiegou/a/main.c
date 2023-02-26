#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int child_pid;
	if((child_pid=fork())==0){
		while(1);
		printf("forbidden zone\n");
		exit(0);
	}
	else{
		while(getc(stdin)){
			kill(child_pid, SIGINT);
			wait(0);
			exit(0);
		}
	}
}
