#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void main(int argc, char * argsv[]){
	int arg = 0;
	if(argc > 0) {
		char cwd[1024];
	   	if (getcwd(cwd, sizeof(cwd)) != NULL)
	       fprintf(stdout,"%s", cwd);
	   	else
	       perror("getcwd() error");
	   }
}