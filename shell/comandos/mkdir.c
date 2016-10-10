#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void main(int argc, char * argsv[]){
	int arg = 0;
	if(argc > 1) {
		int error = mkdir(argsv[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (error < 0)
			printf ("ERROR\n");
	}
	else
		printf("%s necesita 1 argumento\n",argsv[0]);
	

}