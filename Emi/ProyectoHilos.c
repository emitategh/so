#include<stdio.h>
#include<pthread.h>

void* tareaA(){
	int id;
//	for(int i=0;i<10000;i++){
		id= pthread_self();
		printf("TAREA: A --- ID: %i\n",id);
//	};
	pthread_exit(0);
}

void* tareaB(){
	int id;
//	for(int i=0;i<10000;i++){
		id= pthread_self();
		printf("TAREA: B --- ID: %i\n",id);
//	};
	pthread_exit(0);	
}

void* tareaC(){
	int id;
//	for(int i=0;i<10000;i++){
		id= pthread_self();
		printf("TAREA: C --- ID: %i\n",id);
//	};
	pthread_exit(0);
}

void* tareaD(){
	int id;
	//for(int i=0;i<10000;i++){
		id= pthread_self();
		printf("TAREA: D --- ID: %i\n",id);
//	};
	pthread_exit(0);
}

void* tareaE(){
	int id;
	//for(int i=0;i<10000;i++){
		id= pthread_self();
		printf("TAREA: E --- ID: %i\n",id);
	//};
	pthread_exit(0);
}

void main(){
	pthread_t ha,hb,hc,hd,he;
	printf("HOLAAA\n");
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
	//pthread_exit(0);
	
}
