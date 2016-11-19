#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se,scerrar,srepetir,s_norepetir;

void* tareaA(){
	
	while(1){
		
		sem_wait(&sa);

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);	
			sem_post(&sb);
			pthread_exit(0);		
		}

		printf("A - ");

		int repetir = sem_trywait(&srepetir);
		if (repetir == 0){
			sem_post(&sa); // (AoB)(AoB)
		}else{
			int no_repetir = sem_trywait(&s_norepetir);

			if (no_repetir == 0){
				sem_post(&sb);
				sem_post(&srepetir);
			}else{
				sem_post(&sc);
				sem_post(&s_norepetir);

			}
		}


		
	};
	pthread_exit(0);
}

void* tareaB(){
	
	while(1){

		sem_wait(&sb);

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);
			sem_post(&sc);
			pthread_exit(0);		
		}

		printf("B - ");
		sem_post(&sc);
	};
	
}

void* tareaC(){
	
	while(1){

		sem_wait(&sc);

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);
			sem_post(&sd);
			pthread_exit(0);		
		}

		printf("C - ");
		sem_post(&sd);
		
	};
	pthread_exit(0);
}

void* tareaD(){
	
	while(1){
		sem_wait(&sd);

		int close = sem_trywait(&scerrar);
		if (close == 0){
			sem_post(&scerrar);	
			sem_post(&sa);
			pthread_exit(0);		
		}
		/*Espero a que  termine el anterior*/
		printf("D - ");
		sem_post(&se);


		
	};
	pthread_exit(0);
}

void* tareaE(){
	
	int cant = 0;
	while(1){
		sem_wait(&se);

		printf("E \n");
		cant++;
		if (cant == 10){
			sem_post(&scerrar);
			sem_post(&sa);
			pthread_exit(0);
		}
		
		sem_post(&sa);
		
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&scerrar,0,0);
	sem_init(&srepetir,0,1);
	sem_init(&s_norepetir,0,0);

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
