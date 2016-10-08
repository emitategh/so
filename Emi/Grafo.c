#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>



sem_t s1,s2,s3,s4,s5;
void* t1(){
	while(1){
		sem_wait(&s1);
		printf(" --- Nueva vuelta al ciclo ---\n *Estoy en t1\n");
		sem_post(&s2);
		sem_post(&s3);
		sem_post(&s4);
	};
	pthread_exit(0);
}

void* t2(){
	while(1){
		sem_wait(&s2);
		printf(" *Estoy en t2\n");
		sem_post(&s5);
	};
	pthread_exit(0);
}

void* t3(){
	while(1){
		sem_wait(&s3);
		printf(" *Estoy en t3\n");
		sem_post(&s5);
	};
	pthread_exit(0);
}

void* t4(){
	while(1){
		sem_wait(&s4);
		printf(" *Estoy en t4\n");
		sem_post(&s5);
	};
	pthread_exit(0);
}

void* t5(){
	while(1){
		sem_wait(&s5);
		sem_wait(&s5);
		sem_wait(&s5);
		printf(" *Estoy en t5\n");
		sem_post(&s1);
	};
	pthread_exit(0);
}

void main(){
	pthread_t h1,h2,h3,h4,h5;
	
	/*Creo los semaforos*/
	sem_init(&s1,0,1);
	sem_init(&s2,0,0);
	sem_init(&s3,0,0);
	sem_init(&s4,0,0);
	sem_init(&s5,0,0);
	
	/*Creo los hilos*/

	pthread_create (&h1,NULL,(void*) t1,NULL);
	pthread_create (&h2,NULL,(void*) t2,NULL);
	pthread_create (&h3,NULL,(void*) t3,NULL);
	pthread_create (&h4,NULL,(void*) t4,NULL);
	pthread_create (&h5,NULL,(void*) t5,NULL);	


	/*Cierro los hilos*/ 

	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	pthread_join(h3,NULL);
	pthread_join(h4,NULL);
	pthread_join(h5,NULL);
	
	/*Cierro los semaforos*/
	sem_destroy(&s1);
	sem_destroy(&s2);
	sem_destroy(&s3);
	sem_destroy(&s4);
	sem_destroy(&s5);
}