#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t scocinero,scocina,sfuente,scomensal,scomer;

void* cocineroA(){
	while(1){
		
		sem_wait(&scocinero);
		sem_wait(&scocina);
		for(int j=0;j<100;j++){
			sem_post(&sfuente);
			printf("Cocinando: A\n");
		};
		sem_post(&scomensal);
		sem_post(&scomer);
	};
}

void* cocineroB(){
	while(1){
		sem_wait(&scocinero);
		sem_wait(&scocina);
		for(int j=0;j<100;j++){
			sem_post(&sfuente);
			printf("Cocinando: B\n");
		};
		sem_post(&scomensal);
		sem_post(&scomer);
	};
}

void* comensalA(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Juan: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);

			for(int j=0;j<92013;j++){

			};
			printf("Juan: Comiendo\n");
			
		}
		else{
				
			printf("Juan despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void* comensalB(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Roberto: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);

			for(int j=0;j<92013;j++){

			};
			printf("Roberto: Comiendo\n");
			
		}
		else{
				
			printf("Roberto despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void* comensalC(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Gaston: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);

			for(int j=0;j<92013;j++){

			};
			printf("Gaston: Comiendo\n");
			
		}
		else{
				
			printf("Gaston despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void* comensalD(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Cecilia: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);

			for(int j=0;j<92013;j++){

			};
			printf("Cecilia: Comiendo\n");
			
		}
		else{
				
			printf("Cecilia despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void* comensalE(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Wilson: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);

			for(int j=0;j<92013;j++){

			};
			printf("Wilson: Comiendo\n");
			
		}
		else{
				
			printf("Wilson despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void* comensalF(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Cristian: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);
			for(int j=0;j<92013;j++){

			};
			printf("Cristian: Comiendo\n");
			
		}
		else{
				
			printf("Cristian despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void* comensalG(){
	while(1){
		sem_wait(&scomensal);
		sem_wait(&scomer);
		int porciones=sem_trywait(&sfuente);
		if(porciones==0){
			printf("Motorola: Me estoy sirviendo\n");
			sem_post(&scomensal);
			sem_post(&scomer);

			for(int j=0;j<92013;j++){
				//Esto es para dar mas tiempo a que cualquier comensal vuelva a 
				// servirse y hacer mas visible el comportamiento de
				// que solo uno se puede servir pero varios comer al mismo tiempo
			};
			printf("Motorola: Comiendo\n");
			
		}
		else{
				
			printf("Motorola despierta a los cocineros\n");
			sem_post(&scocinero);
			sem_post(&scocinero);
			sem_post(&scocina);
		};
	};
}
void main(){
	pthread_t h1,h2,h3,h4,h5,h6,h7,h8,h9;
	
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


	pthread_create (&h6,NULL,(void*) comensalD,NULL);
	pthread_create (&h7,NULL,(void*) comensalE,NULL);
	pthread_create (&h8,NULL,(void*) comensalF,NULL);
	pthread_create (&h9,NULL,(void*) comensalG,NULL);	
	
	/*Cierro los hilos*/ 
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	pthread_join(h3,NULL);
	pthread_join(h4,NULL);
	pthread_join(h5,NULL);
}
