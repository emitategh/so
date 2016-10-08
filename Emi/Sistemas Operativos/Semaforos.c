#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se;

void* tareaA(){
	for(int i=0;i<20;i++){

		/*Espero*/
		sem_wait(&sa);

		printf("A\n");
		
		/*Seteo el semaforo siguiente*/
		sem_post(&sb);
	};
	pthread_exit(0);
}

void* tareaB(){
	for(int i=0;i<20;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sb);
		printf("B\n");
		
		/*Seteo el semaforo siguiente*/
		sem_post(&sc);
	};
	pthread_exit(0);	
}

void* tareaC(){
	for(int i=0;i<20;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sc);
		printf("C\n");
		
		/*Seteo el semaforo siguiente*/
		sem_post(&sd);
	};
	pthread_exit(0);
}

void* tareaD(){
	for(int i=0;i<20;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&sd);
		printf("D\n");
		
		/*Seteo el semaforo siguiente*/
		sem_post(&se);
	};
	pthread_exit(0);
}

void* tareaE(){
	for(int i=0;i<20;i++){
		/*Espero a que  termine el anterior*/
		sem_wait(&se);
		printf("E\n");
		
		/*Seteo el semaforo actual*/
		sem_post(&sa);
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&sa,0,1);
	sem_init(&sb,0,0);
	sem_init(&sc,0,0);
	sem_init(&sd,0,0);
	sem_init(&se,0,0);
	
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
