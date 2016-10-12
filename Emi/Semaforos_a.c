#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se,scerrar;


void* tareaA(){
	int cant = 0;
	while(1){
		if (cant == 20){
			sem_post(&scerrar);
			sem_post(&sa);
			pthread_exit(0);
		}	
		printf("A\n");
		sem_post(&sa);
		sem_wait(&se);
		cant++;
	};
}

void* tareaB(){
	
	
	
	while(1){

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);	
			pthread_exit(0);		
		}
		/*Espero a que  termine el anterior*/
		sem_wait(&sa);
		printf("B\n");
		sem_post(&sb);
		
	};	
}

void* tareaC(){
	
	while(1){

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);	
			pthread_exit(0);		
		}
		/*Espero a que  termine el anterior*/
		sem_wait(&sb);
		printf("C\n");
		sem_post(&sc);
		
	};
}

void* tareaD(){
	
	while(1){

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);	
			pthread_exit(0);		
		}
		/*Espero a que  termine el anterior*/
		sem_wait(&sc);
		printf("D\n");
		sem_post(&sd);
		
	};
	
}

void* tareaE(){
	
	
	while(1){

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);	
			pthread_exit(0);		
		}
		/*Espero a que  termine el anterior*/
		sem_wait(&sd);
		printf("E\n");
		sem_post(&se);
		
	};
	
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&sa,0,0);
	sem_init(&sb,0,0);
	sem_init(&sc,0,0);
	sem_init(&sd,0,0);
	sem_init(&se,0,0);
	sem_init(&scerrar,0,0);
	
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
	sem_destroy(&scerrar);
}
