#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sab,sc,sd,se,sf,scerrar;

void* tareaA(){
	
	while(1){
		sem_wait(&sab);
		printf("A - ");
		sem_post(&sc);
	};
	pthread_exit(0);
}

void* tareaB(){
	
	while(1){
		sem_wait(&sab);
		printf("B - ");
		sem_post(&sc);
	};
	pthread_exit(0);
}

void* tareaC(){
	
	while(1){
		sem_wait(&sc);
		printf("C - ");
		sem_post(&sd);
		
	};
	pthread_exit(0);
}

void* tareaD(){
	
	while(1){
		sem_wait(&sd);
		printf("D - ");
		sem_post(&se);
		
	};
	pthread_exit(0);
}

void* tareaE(){
	
	
	while(1){
		sem_wait(&se);
		printf("E \n");
		sem_post(&sab);
		
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&scerrar,0,0);
	sem_init(&sab,0,1);
	sem_init(&sc,0,0);
	sem_init(&sd,0,0);
	sem_init(&se,0,0);
	sem_init(&sf,0,0);
	
	
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
	sem_destroy(&sab);
	sem_destroy(&sc);
	sem_destroy(&sd);
	sem_destroy(&se);
	sem_destroy(&scerrar);
}
