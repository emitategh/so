#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se;

void* tareaA(){
	for(int i=0;i<10;i++){
		printf("A\n");
		sem_post(&sa);
		sem_wait(&se);
	};
	pthread_exit(0);
}

void* tareaB(){
	
	
	
	for(int i=0;i<10;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sa);
		printf("B\n");
		sem_post(&sb);
		
	};
	pthread_exit(0);	
}

void* tareaC(){
	
	for(int i=0;i<10;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sb);
		printf("C\n");
		sem_post(&sc);
		
	};
	pthread_exit(0);
}

void* tareaD(){
	
	for(int i=0;i<10;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sc);
		printf("D\n");
		sem_post(&sd);
		
	};
	pthread_exit(0);
}

void* tareaE(){
	
	
	for(int i=0;i<10;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sd);
		printf("E\n");
		sem_post(&se);
		
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	printf("HOLA2\n");
	sem_init(&sa,0,0);
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


	/*Cierro los hilos*/ 

	pthread_join(ha,NULL);
	pthread_join(hb,NULL);
	pthread_join(hc,NULL);
	pthread_join(hd,NULL);
	pthread_join(he,NULL);
	
	/*Cierro los semaforos*/
	sem_destroy(&sa);
	sem_destroy(&sb);
	sem_destroy(&sc);
	sem_destroy(&sd);
	sem_destroy(&se);
}
