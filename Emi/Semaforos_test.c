#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se;

void* tareaA(){
	for(int i = 0; i < 100;i++){
		int sval;
		int ret = sem_getvalue(&sa,&sval);	
		printf("sa %i\n",sval);
	}
	sem_post(&sa);
	pthread_exit(0);
}

void* tareaB(){			
	printf("Estoy en B\n");
	sem_wait(&sa);			
	printf("B Libere A\n");
	
	
	pthread_exit(0);	
}

void* tareaC(){
	printf("Estoy en C\n");
	sem_wait(&sa);
	printf("C Libere A\n");
	pthread_exit(0);
}

void* tareaD(){
	printf("Estoy en D\n");
	sem_wait(&sa);
	printf("D Libere A\n");
	pthread_exit(0);
}

void* tareaE(){
	
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	printf("HOLA2\n");
	sem_init(&sa,0,2);
	sem_init(&sb,0,0);
	sem_init(&sc,0,0);
	sem_init(&sd,0,0);
	sem_init(&se,0,0);
	
	printf("HOLA\n");
	/*Creo los hilos*/

	pthread_create (&ha,NULL,(void*) tareaA,NULL);
	pthread_create (&hb,NULL,(void*) tareaB,NULL);
	pthread_create (&hc,NULL,(void*) tareaC,NULL);
	pthread_create (&hd,NULL,(void*) tareaD,NULL);
	pthread_create (&he,NULL,(void*) tareaE,NULL);	

	/*Cierro los semaforos

	sem_destroy(&sa);
	sem_destroy(&sb);
	sem_destroy(&sc);
	sem_destroy(&sd);
	sem_destroy(&se);

	/*Cierro los hilos*/ 

	pthread_join(ha,NULL);
	pthread_join(hb,NULL);
	pthread_join(hc,NULL);
	pthread_join(hd,NULL);
	pthread_join(he,NULL);
	
}
