#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

typedef struct{

    long tipo;
    char ch;

} mensaje;

// PARA REFERENCIAS http://www.chuidiang.com/clinux/ipcs/colas.php

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define size sizeof(mensaje)-sizeof(long)

int main(){
	//CREO UNA CLAVE CON DATOS LA FUNCION FTOK Y UN FICHERO QUE EXISTA, Y UN NUMERO
	key_t key=ftok("/usr",13);

	//CHEQUEO SI NO EXISTE UNA COLA PREVIAMENTE CON ESA CLAVE
	int oldId=msgget(key, 0);
	if(oldId!=-1)
		if(msgctl(oldId, IPC_RMID, NULL)!=-1)
			printf("Cola anterior eliminada\n");

	//CREO LA COLA QUE UTILIZARE, CON PERMISOS DE 0666 (ESCRITURA/LECTURA)
	int id_queue=msgget(key, IPC_CREAT|0666);

	//CREO EL MENSAJE QUE ENVIARE
	mensaje sms;
	sms.tipo=A;

	//ENVIO EL MENSAJE PARA ARRANCAR
	msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
	pid_t pA=fork();
	if(pA==0)
		procesoA();

	pid_t pB=fork();
	if(pB==0)
		procesoB();
	pid_t pC=fork();
	if(pC==0)
		procesoC();

	pid_t pD=fork();
	if(pD==0)
		procesoD();

	pid_t pE=fork();
	if(pE==0)
		procesoE();
	
	wait(NULL);
	return 0;
};

void procesoA(){
	//ME CONECTO A LA COLA

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;

	int a=0;
	while(1){

		msgrcv(id_queue,(struct msgbuf*)&sms,size,A,0);

		if(a==0){
			a++;
			sleep(1);
			printf("A - ");
			fflush(NULL);
			sms.tipo=A;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		}
		else{
			if(a==2)
				a=0;
			else a++;
			sleep(1);
			printf("A - ");
			fflush(NULL);
			sms.tipo=B;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		};

	}
};

void procesoB(){
	//ME CONECTO A LA COLA

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;

	while(1){

		//ESPERO A RECIBIR B
		msgrcv(id_queue,(struct msgbuf*)&sms,size,B,0);
		sleep(1);
		printf("B - ");
		fflush(NULL);

		sms.tipo=C;
		msgsnd(id_queue,(struct msgbuf*)&sms,size,0);

	}
};
void procesoC(){
	//ME CONECTO A LA COLA

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;

	while(1){

		//ESPERO A RECIBIR B
		msgrcv(id_queue,(struct msgbuf*)&sms,size,C,0);
		sleep(1);
		printf("C - ");
		fflush(NULL);

		sms.tipo=D;
		msgsnd(id_queue,(struct msgbuf*)&sms,size,0);

	}
};
void procesoD(){
	//ME CONECTO A LA COLA

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;

	while(1){

		//ESPERO A RECIBIR B
		msgrcv(id_queue,(struct msgbuf*)&sms,size,D,0);
		sleep(1);
		printf("D - ");
		fflush(NULL);

		sms.tipo=E;
		msgsnd(id_queue,(struct msgbuf*)&sms,size,0);

	}
};
void procesoE(){
	//ME CONECTO A LA COLA

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;
	int e=0;
	while(1){

		//ESPERO A RECIBIR B
		msgrcv(id_queue,(struct msgbuf*)&sms,size,E,0);

		if(e==0){
			e++;
			printf("E.\n");
			fflush(NULL); //NI IDEA
			sms.tipo=A;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		}
		else if(e==1){
				printf("E - ");
				fflush(NULL); //NI IDEA
				sms.tipo=E;
				msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
				e++;
			}
			else{
				printf("E.\n");
				fflush(NULL);
				sms.tipo=A;
				e=0;
				msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
			};
	}

};


