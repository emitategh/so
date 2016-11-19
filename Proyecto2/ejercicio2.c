#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define n 10
#define size sizeof(mensaje)-sizeof(long)
#define oso 1
#define abeja 2

typedef struct{

    long tipo;
    int fuente [n];

} mensaje;

int main(){
	//CREO UNA CLAVE CON DATOS LA FUNCION FTOK Y UN FICHERO QUE EXISTA, Y UN NUMERO
	key_t key=ftok("/usr",13);

	//CHEQUEO SI NO EXISTE UNA COLA PREVIAMENTE CON ESA CLAVE
	int oldId=msgget(key, 0);
	if(oldId!=-1)
		if(msgctl(oldId, IPC_RMID, NULL)!=-1)
			printf("Cola anterior eliminada\n");

	//CREO LA COLA DE MENSAJES 
	int id_queue=msgget(key, IPC_CREAT|0666);
	mensaje sms;
	sms.tipo=abeja;

	//ENVIO EL PRIMER MSJ
	msgsnd(id_queue,(struct msgbuf*)&sms,size,0);

	pid_t pA=fork();
	if(pA==0)
		abejas();		
	
	pid_t pO=fork();
	if(pO==0)
		osos();

	wait(NULL);
	return 0;
};

void abejas(){
	//COMIENZO A ESCUCHAR LA COLA DE MSJ

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;
	int i=0;
	while(1){
		msgrcv(id_queue,(struct msgbuf*)&sms,size,abeja,0);
		printf("ABEJA: Cocinando porcion: %i de miel.\n",i);
		if(i!=n-1){
			//SI HAY LUGAR INSERTO UNA PORCION
			sms.fuente[i]=1;
			sms.tipo=abeja;
			i++;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		}
		else{
			//SI LLENE LA FUENTE DE PORCIONES LLAMO AL OSO
			sms.fuente[i]=1;
			sms.tipo=oso;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
			i=0;
		};
	};
};

void osos(){
	//COMIENZO A ESCUCHAR LA COLA DE MSJ

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;
	int i=0;
	while(1){
		msgrcv(id_queue,(struct msgbuf*)&sms,size,oso,0);
		printf("OSO: Comiendo porcion: %i de miel.\n",i);
		if(i!=n-1){
			//SI QUEDAN PORCIONES COMO UNA
			sms.fuente[i]=0;
			sms.tipo=oso;
			i++;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		}
		else{
			//SI NO QUEDAN PORCIONES LLAMO A LAS ABAJAS
			sms.fuente[i]=0;
			sms.tipo=abeja;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
			i=0;
		};
	};
};
