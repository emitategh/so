#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t scocinero,scocina,sfuente,scerrado,scomensal,scomer;

void* cocineroA(){
	int i=0;
	while(i!=5){
		
		sem_wait(&scocinero);
		sem_wait(&scocina);
		int close=sem_trywait(&scerrado);
		if(close==0){
			sem_post(&scerrado);
			printf("Estoy cerrando A\n");
			pthread_exit(0);
		}
		else{
			for(int j=0;j<100;j++){
				sem_post(&sfuente);
				printf("Cocinando: A\n");
			};
			sem_post(&scomensal);
			sem_post(&scomer);
		};
		i++;
		if(i==5){
			printf("VOY A CERRAR A\n");
			sem_post(&scerrado);
		};
	};
}

void* cocineroB(){
	int i=0;
	while(i!=5){
		sem_wait(&scocinero);
		sem_wait(&scocina);
		int close=sem_trywait(&scerrado);
		if(close==0){
			sem_post(&scerrado);
			printf("Estoy cerrando B\n");
			pthread_exit(0);
		}
		else{
			for(int j=0;j<100;j++){
				sem_post(&sfuente);
				printf("Cocinando: B\n");
			};
			sem_post(&scomensal);
			sem_post(&scomer);
		};
		i++;
		if(i==5){
			printf("VOY A CERRAR B\n");
			sem_post(&scerrado);
			
		};
	};
}

void* comensalA(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int close=sem_trywait(&scerrado);
		if(close==0){
			sem_post(&scerrado);
			int porciones=sem_trywait(&sfuente);
			if(porciones==0){
				printf("Juan: Me estoy sirviendo\n");
				sem_post(&scomensal);
				sem_post(&scomer);				
				printf("Juan: Comiendo\n");
			};
			printf("Termine de comer Juan\n");
			sem_post(&scocinero);
			sem_post(&scocina);
			pthread_exit(0);
		}
		else{
			int porciones=sem_trywait(&sfuente);
			if(porciones==0){
				printf("Juan: Me estoy sirviendo\n");
				sem_post(&scomensal);
				sem_post(&scomer);
				printf("Juan: Comiendo\n");
				
			}
			else{
				
				printf("Juan despierta a los cocineros\n");
				sem_post(&scocinero);
				sem_post(&scocinero);
				sem_post(&scocina);
			};
		};
	};
}
void* comensalB(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int close=sem_trywait(&scerrado);
		if(close==0){
			sem_post(&scerrado);
			int porciones=sem_trywait(&sfuente);
			if(porciones==0){
				printf("Comiendo Pedro\n");
				sem_post(&scomensal);
				sem_post(&scomer);
			};
			printf("Termine de comer Pedro\n");
			sem_post(&scocinero);
			sem_post(&scocina);
			pthread_exit(0);
		}
		else{
			int porciones=sem_trywait(&sfuente);
			if(porciones==0){
				printf("Pedro: Me estoy sirviendo\n");
				sem_post(&scomensal);
				sem_post(&scomer);
				printf("Pedro: Comiendo\n");
			}
			else{
				printf("Pedro despierta a los cocineros\n");
				sem_post(&scocinero);
				sem_post(&scocinero);
				sem_post(&scocina);
			};
		};
	};
}
void* comensalC(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int close=sem_trywait(&scerrado);
		if(close==0){
			sem_post(&scerrado);
			int porciones=sem_trywait(&sfuente);
			if(porciones==0){
				printf("Gaston: Me estoy sirviendo\n");
				sem_post(&scomensal);
				sem_post(&scomer);
				printf("Gaston: Estoy comiendo\n");
			};
			printf("Termine de comer Gaston\n");
			sem_post(&scocinero);
			sem_post(&scocina);
			pthread_exit(0);
		}
		else{
			int porciones=sem_trywait(&sfuente);
			if(porciones==0){
				printf("Gaston: Me estoy sirviendo\n");
				sem_post(&scomensal);
				sem_post(&scomer); //HABILITA LA FUENTE PARA COMER
				printf("Gaston: Estoy comiendo\n");
			}
			else{
				printf("Gaston despierta a los cocineros\n");
				sem_post(&scocinero);
				sem_post(&scocinero);
				sem_post(&scocina);
			};
		};
	};
}
void main(){
	pthread_t h1,h2,h3,h4,h5;
	
	/*Creo los semaforos*/
	sem_init(&scocinero,0,1);
	sem_init(&scocina,0,1);
	sem_init(&scomensal,0,0);
	sem_init(&scomer,0,0);
	sem_init(&sfuente,0,0);
	
	/*Creo los hilos*/
	pthread_create (&h1,NULL,(void*) cocineroA,NULL);
	pthread_create (&h2,NULL,(void*) cocineroB,NULL);
	pthread_create (&h3,NULL,(void*) comensalA,NULL);
	pthread_create (&h4,NULL,(void*) comensalB,NULL);
	pthread_create (&h5,NULL,(void*) comensalC,NULL);	
	
	/*Cierro los hilos*/ 
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	pthread_join(h3,NULL);
	pthread_join(h4,NULL);
	pthread_join(h5,NULL);
}
