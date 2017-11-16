#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <dirent.h>


int i = 5;
int main(void){

FILE* file = fopen("output.txt", "w");

pid_t parent = getpid();
pid_t id = fork();


	if (id==0){


		fprintf(file,"I am a child: my pid is: %d+ %d\n", getpid(),i);
		
		fflush(stdout);
	}else{
		id =fork();


	}
	
	if (id==0){
		fflush(stdout);
		fprintf(file,"I am a second Child my pid is: %d +%d\n",getpid(),i);
		fflush(stdout);

	}else{
		fflush(stdout);
		fprintf(file,"I am parent waiting on both of my child to finish:");
		
		pid_t i;

		wait(NULL);
		wait(NULL);
		fprintf(file,"my chilren are finished\nmy pid is: %d\nsecond child: %d\n",getpid(),id);
	
		

	}
return 0;



}
