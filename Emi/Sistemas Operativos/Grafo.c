#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s1,s2,s3,s4,s5,s6,si;
//int a=1;
void* p1(){
	for(int i=0;i<5;i++){
		sem_wait(&s1);
		printf("P1 - ");
		sem_post(&s2);
		sem_post(&s3);
		sem_post(&s4);
	};
	pthread_exit(0);
}
void* p2(){
	for(int i=0;i<5;i++){
		sem_wait(&s2);
		printf("P2 - ");
		sem_post(&s6);
	};
	pthread_exit(0);
}
void* p3(){
	for(int i=0;i<5;i++){
		sem_wait(&s3);
		sem_wait(&s3);
		sem_wait(&s3);
		printf("P3 - ");
		sem_post(&s6);
	};
	pthread_exit(0);
}
void* p4(){
	for(int i=0;i<5;i++){
		sem_wait(&s4);	
		printf("P4 - ");
		sem_post(&s3);
		sem_post(&s5);
	};
	pthread_exit(0);
}
void* p5(){int a=1;
	for(int i=0;i<5;i++){
		sem_wait(&s5);
		printf("P5 - ");
		sem_post(&s3);
		sem_post(&s6);
	};
	pthread_exit(0);
}
void* p6(){
	for(int i=0;i<5;i++){
		sem_wait(&s6);
		sem_wait(&s6);
		sem_wait(&s6);
		printf("P6\n");
		sem_post(&si);
	};
	//a=0;
	pthread_exit(0);
}
void* pi(){
	for(int i=0;i<5;i++){
		sem_wait(&si);
		printf("--- Nueva cadena numero: %i ---\n",i);
		sem_post(&s1);	
	};
	pthread_exit(0);
}
void main(){
	pthread_t h1,h2,h3,h4,h5,h6,hi;

	sem_init(&s1,0,0);
	sem_init(&s2,0,0);
	sem_init(&s3,0,0);
	sem_init(&s4,0,0);
	sem_init(&s5,0,0);
	sem_init(&s6,0,0);
	sem_init(&si,0,1);

	pthread_create (&h1,NULL,(void*) p1,NULL);
	pthread_create (&h2,NULL,(void*) p2,NULL);
	pthread_create (&h3,NULL,(void*) p3,NULL);
	pthread_create (&h4,NULL,(void*) p4,NULL);
	pthread_create (&h5,NULL,(void*) p5,NULL);
	pthread_create (&h6,NULL,(void*) p6,NULL);
	pthread_create (&hi,NULL,(void*) pi,NULL);
	
	pthread_join(h1,NULL);
	pthread_join(h2,NULL);
	pthread_join(h3,NULL);
	pthread_join(h4,NULL);
	pthread_join(h5,NULL);
	pthread_join(h6,NULL);
	pthread_join(hi,NULL);
}
