#include<stdio.h>
#include<pthread.h>

void* tareaA(){
	for(int i=0;i<10000;i++)
		printf("TAREA: A\n");
	pthread_exit(0);
}

void* tareaB(){
	for(int i=0;i<10000;i++)
		printf("TAREA: B\n");
	pthread_exit(0);	
}

void* tareaC(){
	for(int i=0;i<10000;i++)
		printf("TAREA: C\n");
	pthread_exit(0);
}

void* tareaD(){
	for(int i=0;i<10000;i++)
		printf("TAREA: D\n");
	pthread_exit(0);
}

void* tareaE(){
	for(int i=0;i<4;i++)
		printf("TAREA: E\n");
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	printf("HOLAAA\n");
	/*Creo los hilos*/
	pthread_create (&ha,NULL,(void*) tareaA,NULL);
	pthread_create (&hb,NULL,(void*) tareaB,NULL);
	pthread_create (&hc,NULL,(void*) tareaC,NULL);
	pthread_create (&hd,NULL,(void*) tareaD,NULL);
	pthread_create (&he,NULL,(void*) tareaE,NULL);	
	
	/*Cierro los hilos*/ 
	pthread_join(ha,NULL);
	pthread_join(hb,NULL);
	pthread_join(hc,NULL);
	pthread_join(hd,NULL);
	pthread_join(he,NULL);
	//pthread_exit(0);
	
}
