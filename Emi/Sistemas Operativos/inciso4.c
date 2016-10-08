#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sab,sc,sd,se;
int a=0;
int end=0;
int j=0;

void* tareaA(){
	for(j;j<24;j++){
		sem_wait(&sab);
		if ((a==0)&&(end!=1)){
			printf("A con a=%i\n",a);
			a++;
			sem_post(&sab);
		}
		else if((a==1)&&(end!=1)){
			printf("A con a=%i\n",a);
			a++;
			sem_post(&sc);
		}
		else if((a==2)&&(end!=1)){
			printf("A con a=%i\n",a);
			a=0;
			sem_post(&sc);
		};
	};
	end=1;
	sem_post(&sab);
	sem_post(&sc);
	pthread_exit(0);
}

void* tareaB(){
	for(j;j<24;j++){
		sem_wait(&sab);
		if ((a==0)&&(end!=1)){
			printf("B con a=%i\n",a);
			a++;
			sem_post(&sab);
		}
		else if((a==1)&&(end!=1)){
			printf("B con a=%i\n",a);
			a++;
			sem_post(&sc);
		}
		else if((a==2)&&(end!=1)){
			printf("B con a=%i\n",a);
			a=0;
			sem_post(&sc);
		};
	};
	end=1;
	sem_post(&sab);
	sem_post(&sc);
	pthread_exit(0);
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
			sem_post(&sab);
		}
		else if (a==0){
			printf("E\n");
			sem_post(&sab);
		};
	};
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&sab,0,1);
	//sem_init(&sb,0,0);
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
