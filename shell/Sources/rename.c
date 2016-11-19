#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void main(int argc, char * argsv[]){
	int arg = 0;
	if(argc > 2) {
		int error = rename (argsv[1],argsv[2]);
		if (error < 0)
			printf ("ERROR\n");
	}
	else
		printf("%s necesita 1 argumento\n",argsv[0]);
}
