#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char * argsv[]){
	int arg = 0;
	//printf("argc %i\n",argc);
	if(argc > 1) {
		int error = rmdir (argsv[1]);
		if (error < 0)
			printf ("ERROR\n");
		
	}
	else
		printf("%s necesita 1 argumento\n",argsv[0]);

}