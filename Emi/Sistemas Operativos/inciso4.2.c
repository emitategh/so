#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sab,saa,sc,sd,se,ss;

void* tareaA(){
	int cant = 0;
	int send_val;
	int ret = sem_getvalue(&ss,&send_val); 
	while(send_val == 0){

		ret = sem_getvalue(&ss,&send_val);
		sem_wait(&sab);

		if (cant == 20){
			sem_post(&ss);
			sem_post(&sb);
			pthread_exit(0);
		}	

		cant++;

		saa_ret = sem_getvalue(&saa,&saa_val);
		
		if (saa_val < 2){
			printf("A \n");
			sem_post(&saa);
			sem_post(&sab);
		}else if(saa_val == 2){
			sem_post(&sc);
			sem_post(&saa);
		}else if(saa_val == 3){
			printf("A \n");	

			sem_wait(&saa);
			sem_wait(&saa);
			sem_wait(&saa);

			sem_post(&sb);
		}

		if (saa_val == 2 || saa_val == 3){
			sem_wait(&sa);
		}

	};
	pthread_exit(0);
}

void* tareaB(){
	int send_val;
	int ret = sem_getvalue(&ss,&send_val); 
	while(send_val == 0){
		ret = sem_getvalue(&ss,&send_val);
		sem_wait(&sab);
		saa_ret = sem_getvalue(&saa,&saa_val);
		
		if (saa_val < 2){
			printf("B \n");	
			sem_post(&sab);|
		}else if(saa_val == 2){
			sem_post(&sc);
			sem_post(&saa);
		}else if(saa_val == 3){
			printf("B \n");	

			sem_wait(&saa);
			sem_wait(&saa);
			sem_wait(&saa);

			sem_post(&sc);
		}


		if (saa_val == 2 || saa_val == 3){
			sem_wait(&sb);
		}
	};
	pthread_exit(0);
}


void* tareaC(){
	/*Espero a que  termine el anterior*/
	int sc_val,sval;
	int ret = sem_getvalue(&ss,&sval);
	while(sval == 0){
		sem_wait(&sc);
		int ret = sem_getvalue(&ss,&sval);
		int sa_ret = sem_getvalue(&sc,&sc_val);
		
		
		if (sval == 0){
			printf("C \n");
		}	

		/*Seteo el semaforo siguiente*/
		sem_post(&sd);
	};
	
	pthread_exit(0);
}


void* tareaD(){
	int sval;
	int ret = sem_getvalue(&ss,&sval);
	while(sval == 0){		
		sem_wait(&sd);
		int ret = sem_getvalue(&ss,&sval);
		/*Espero a que  termine el anterior*/
		if (sval == 0){
			printf("D\n");
		}

		/*Seteo el semaforo siguiente*/
		sem_post(&se);
	};


	pthread_exit(0);
}


void* tareaE(){
	int sval;	
	int ret = sem_getvalue(&ss,&sval);
	while(sval == 0){
		/*Espero a que  termine el anterior*/
		sem_wait(&se);
		int ret = sem_getvalue(&ss,&sval);
		if (sval == 0){
			printf("E\n");
		}

		/*Seteo el semaforo siguiente*/	
		sem_post(&sa);
	};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	
	/*Creo los semaforos*/
	sem_init(&sa,0,0);
	sem_init(&saa,0,0);
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
	
	/*Cierro los hilos*/ 
	pthread_join(ha,NULL);
	pthread_join(hb,NULL);
	pthread_join(hc,NULL);
	pthread_join(hd,NULL);
	pthread_join(he,NULL);
	
	/*Cierro los semaforos*/

}
