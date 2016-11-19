#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void main(int argc, char * argsv[]){
	int arg = 0;
	time_t seconds;
	seconds = time(NULL);
	printf("Horas desde el 1 de Enero de 1970 = %ld\n", seconds/3600);
}
