#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se;
int a=0;
int end=0;

void* tareaA(){
	int n=24;
	for(int i=0;i<n;i++){
		sem_wait(&sa);
		if (a==0){
			printf("A con a=%i\n",a);
			a++;
		}
		else if(a==1){
			printf("A con a=%i\n",a);
			a++;
			sem_post(&sc);
		}
		else if(a==2){
			printf("A con a=%i\n",a);
			a=0;
			if(i!=(n-1))
				sem_post(&sb);
		};
	};
	end=1;
	sem_post(&sb);
	pthread_exit(0);
}

void* tareaB(){
	for(int i=0;i<16;i++){
		sem_wait(&sb);
		if(end==1){
			printf("B\n");
			sem_post(&sc);
			pthread_exit(0);
		}
		else{
			printf("B\n");
			
			/*Seteo el semaforo actual*/
			sem_post(&sc);
		};
	};	
}

void* tareaC(){
	for(int i=0;i<16;i++){
		sem_wait(&sc);
		if(end==1){
			printf("C\n");
			sem_post(&sd);
			pthread_exit(0);
		}
		else{
			printf("C\n");

			/*Seteo el semaforo actual*/
			sem_post(&sd);
		};
	};	
}
void* tareaD(){
	for(int i=0;i<16;i++){
		sem_wait(&sd);
		if(end==1){
			printf("D\n");
			sem_post(&se);
			pthread_exit(0);
		}
		else{
			printf("D\n");

			/*Seteo el semaforo actual*/
			sem_post(&se);
		};
	};	
}

void* tareaE(){
	for(int i=0;i<16;i++){
		sem_wait(&se);
		if(end==1){
			printf("E\n");
			pthread_exit(0);
		}
		else if (a==2){
			printf("E\n");
			sem_post(&sa);
		}
		else if (a==0){
			printf("E\n");
			sem_post(&sa);
			sem_post(&sa);
		};
	};
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&sa,0,2);
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

}
