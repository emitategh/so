#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sa,sb,sc,sd,se,ss,send;


void* tareaA(){
	int n=24;
	int sval;
	int a;

	for(int i=0;i<n;i++){
		sem_wait(&sa);
		a = sem_getvalue(&ss,&sval);

		if (sval == 0){
			printf("A con a=%i\n",sval);
			sem_post(&ss);
		}
		else if(sval == 1){
			printf("A con a=%i\n",sval);
			sem_post(&ss);
			sem_post(&sc);
		}
		else if(sval == 2){
			printf("A con a=%i\n",sval);
			// reset de ss
			sem_wait(&ss);
			sem_wait(&ss);

			if(i!=(n-1))
				sem_post(&sb);
		};
	};
	sem_post(&send);

	sem_post(&sb);
	pthread_exit(0);
}

void* tareaB(){
	int send_val;
	int end;
	for(int i=0;i<16;i++){
		sem_wait(&sb);
		end = sem_getvalue(&send,&send_val);
		if(send_val){
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
	int send_val;
	int end;
	for(int i=0;i<16;i++){
		sem_wait(&sc);
		end = sem_getvalue(&send,&send_val);
		if(send_val){
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
	int send_val;
	int end;
	for(int i=0;i<16;i++){
		sem_wait(&sd);
		end = sem_getvalue(&send,&send_val);
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
	int send_val,sval;
	int end,a;
	for(int i=0;i<16;i++){
		sem_wait(&se);
		end = sem_getvalue(&send,&send_val);
		a = sem_getvalue(&ss,&sval);
		if(send_val){
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
	sem_init(&ss,0,0);
	sem_init(&send,0,0);
	
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
