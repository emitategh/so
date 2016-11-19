#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sab,sc,sd,se,sf,scerrar,srepetir,s_norepetir;

void* tareaA(){
	
	while(1){
		
		sem_wait(&sab);

		int close = sem_trywait(&scerrar);
		if (close == 0){
			//printf("\nSaliendo de tareaA\n");
			sem_post(&scerrar);	
			sem_post(&sab);
			pthread_exit(0);		
		}

		printf("A - ");

		int repetir = sem_trywait(&srepetir);
		if (repetir == 0){
			sem_post(&sab); // (AoB)(AoB)
		}else{
			int no_repetir = sem_trywait(&s_norepetir);

			if (no_repetir == 0){
				sem_post(&sc);
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

		
		sem_wait(&sab);
		

		int close = sem_trywait(&scerrar);

		if (close == 0){
			//printf("\nSaliendo de tareaB\n");
			sem_post(&scerrar);
			sem_post(&sc);	
			pthread_exit(0);		
		}


		printf("B - ");

		int repetir = sem_trywait(&srepetir);
		if (repetir == 0){
			sem_post(&sab); // (AoB)(AoB)
		}else{
			int no_repetir = sem_trywait(&s_norepetir);

			if (no_repetir == 0){
				sem_post(&sc);
				sem_post(&srepetir);
			}else{
				sem_post(&sc);
				sem_post(&s_norepetir);

			}
		}
	};
	
}

void* tareaC(){
	
	while(1){

		sem_wait(&sc);

		int close = sem_trywait(&scerrar);
		if (close == 0){
			//printf("\nSaliendo de tareaC\n");
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
			//printf("\nSaliendo de tareaD\n");
			sem_post(&scerrar);	
			sem_post(&sab);
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

		/*Espero a que  termine el anterior*/
		printf("E \n");
		cant++;
		if (cant == 20){
			printf("\nSaliendo de tareaE\n");
			sem_post(&scerrar);
			sem_post(&sab);
			pthread_exit(0);
		} 
		
		sem_post(&sab);
		
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&scerrar,0,0);
	sem_init(&srepetir,0,1);
	sem_init(&s_norepetir,0,0);

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
}
