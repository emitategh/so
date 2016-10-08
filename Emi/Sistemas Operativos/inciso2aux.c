#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sab,sc,sd,se;
int a=1;
void* tareaA(){
	for(int i=0;i<20;i++){
		sem_wait(&sab);
		if(a!=0)
			printf("A\n");
		else{
			sem_post(&sab);
			pthread_exit(0);
		};
		sem_post(&sc);
	};
}
/*		if (a==0){
			sem_post(&sab);
			pthread_exit(0);
		}
		else{
			sem_wait(&sab);
			if(a!=0)
				printf("A\n");
			
			/*Seteo el semaforo siguiente	
			sem_post(&sc);
		};
	};
}
*/
void* tareaB(){
	/*Espero a que  termine el anterior*/
	for(int i=0;i<20;i++){
		sem_wait(&sab);
		if(a!=0)
			printf("B\n");
		else{
			sem_post(&sab);
			pthread_exit(0);
		};
		sem_post(&sc);
	};
}

/*
		if (a==0){
			sem_post(&sab);
			pthread_exit(0);
		}
		else{
			sem_wait(&sab);
			if(a!=0)
				printf("B\n");

			/*Seteo el semaforo siguiente
			sem_post(&sc);
		};
	};
}
*/
void* tareaC(){
	/*Espero a que  termine el anterior*/
	for(int i=0;i<20;i++){
		sem_wait(&sc);
		printf("C\n");

		/*Seteo el semaforo siguiente*/
		sem_post(&sd);
	};
	a=0;	
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

		/*Seteo el semaforo siguiente*/	
		sem_post(&sab);
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	//sem_init(&sa,0,0);
	sem_init(&sab,0,1);
	sem_init(&sc,0,0);
	sem_init(&sd,0,0);
	sem_init(&se,0,0);
	
	/*Creo los hilos*/

	pthread_create (&ha,NULL,(void*) tareaA,NULL);
	pthread_create (&hb,NULL,(void*) tareaB,NULL);
	pthread_create (&hc,NULL,(void*) tareaC,NULL);
	pthread_create (&hd,NULL,(void*) tareaD,NULL);
	pthread_create (&he,NULL,(void*) tareaE,NULL);	

	/*Cierro los semaforos*/

	//sem_destroy(&sa);
	sem_destroy(&sab);
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
