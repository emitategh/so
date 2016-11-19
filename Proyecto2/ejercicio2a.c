#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/shm.h> 
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct{
	int porciones_vacias; //INDICA CUANTOS LUGARES DISPONIBLES HAY EN LA FUENTE
	int estado_oso; //INDICA EL ESTADO DEL OSO 
	sem_t mutex; //PARA SINCRONIZAR A LAS ABEJAS
} memoria;

#define durmiendo 0
#define despierto 1
#define n 10
#define size sizeof(memoria)

int main(){
	//GENERO LA CLAVE DE LA SECCION DE LA MEMORIA COMPARTIDA
	key_t key=ftok("/usr",139);
	int id_mem=shmget(key,size,IPC_CREAT|0666);
	
	//ASIGNO LA SECCION DE MEMORIA A MEM
	memoria* mem=(memoria*) shmat(id_mem,NULL,0);

	//INICIO EL ESTADO DEL OSO COMO DURMIENDO Y LAS ABEJAS PARA COCINAR
	mem->porciones_vacias=n;
	mem->estado_oso=durmiendo;
	sem_init(&(mem->mutex),0,1);

	for(int j=0;j<3;j++){
		pid_t pid=fork();
		if(pid==0)
			abejas(j);
	};

	pid_t pO=fork();
	if(pO==0)
		oso();
	wait(NULL);
	return 0;
};

void abejas(int id){
	//GENERO LA CLAVE DE LA SECCION DE LA MEMORIA COMPARTIDA
	key_t key=ftok("/usr",139);
	int id_mem=shmget(key,size,IPC_CREAT|0666);
	
	//ASIGNO LA SECCION DE MEMORIA A MEM
	memoria* mem=(memoria*) shmat(id_mem,NULL,0);

	while(1){
		if(sem_trywait(&(mem->mutex))==0){
		//SI SOY LA UNICA ABEJA TRABAJANDO
			if(mem->estado_oso==durmiendo){
				//SI EL OSO ESTA DURMIENDO
				if(mem->porciones_vacias!=0){
					sleep(1);
					printf("Abeja: %i : cocinando una porcion de miel --- PORCIONES VACIAS: %i\n",id,mem->porciones_vacias);
					//int puntero=mem->porcion;
					//*(mem->fuente+puntero)=1; // ES REALMENTE NECESARIO EL BUFFER?
					mem->porciones_vacias--;
				}
				else{
					sleep(1);
					printf("Abeja: %i : despierta al oso\n",id);
					mem->estado_oso=despierto;
				}
			sem_post(&(mem->mutex));
			};
		};
	};
};

void oso(){
	//GENERO LA CLAVE DE LA SECCION DE LA MEMORIA COMPARTIDA
	key_t key=ftok("/usr",139);
	int id_mem=shmget(key,size,IPC_CREAT|0666);
	
	//ASIGNO LA SECCION DE MEMORIA A MEM
	memoria* mem=(memoria*) shmat(id_mem,NULL,0);

	while(1){
		if(mem->estado_oso==despierto){
		//SI EL OSO ESTA DURMIENDO
			if(mem->porciones_vacias!=n){
				sleep(1);
				printf("Oso: comiendo una porcion de miel\n");
				//int puntero=mem->porcion;
				//*(mem->fuente+puntero)=1; // ES REALMENTE NECESARIO EL BUFFER?
				mem->porciones_vacias++;
			}
			else{
				sleep(1);
				printf("Oso: se va a dormir y avisa a las abejas que cocinen\n");
				mem->estado_oso=durmiendo;
			}
		sem_post(&(mem->mutex));
		}
	};
};