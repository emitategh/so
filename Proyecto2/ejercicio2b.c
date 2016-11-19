#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define n 10 //CANTIDAD DE PORCIONES
#define m 3 //CANTIDAD DE ABEJAS
#define size sizeof(mensaje)-sizeof(long)
#define oso 1
#define abeja 2

typedef struct{

    long tipo;
    int fuente; //INDICA LA CANTIDAD DE LUGARES LIBRES EN LA FUENTE

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
	sms.fuente=n;

	//ENVIO EL PRIMER MSJ
	msgsnd(id_queue,(struct msgbuf*)&sms,size,0);

	for(int i=0;i<m;i++){
		pid_t pA=fork();
		if(pA==0)
			abejas(i);		
	};
	pid_t pO=fork();
	if(pO==0)
		osos();

	wait(NULL);
	return 0;
};

void abejas(int id){
	//COMIENZO A ESCUCHAR LA COLA DE MSJ

	key_t key=ftok("/usr",13);
	int id_queue=msgget(key,0);
	mensaje sms;
	while(1){
		msgrcv(id_queue,(struct msgbuf*)&sms,size,abeja,0);
		sleep(2);
		if(sms.fuente==0){
			
			printf("ABEJA:%i : Despierta al oso.\n",id);
			//SI LLENE LA FUENTE DE PORCIONES LLAMO AL OSO
			sms.fuente--;
			sms.tipo=oso;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		}
		else{
			//SI HAY LUGAR INSERTO UNA PORCION
			printf("ABEJA:%i : Cocinando porcion de miel.\n",id);
			sms.fuente--;
			sms.tipo=abeja;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
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
		if(sms.fuente!=n-1){
			//SI QUEDAN PORCIONES COMO UNA PORCION

			printf("OSO: Comiendo porcion:%i de miel.\n",i);
			i++;
			sms.fuente++;
			sms.tipo=oso;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
		}
		else{
			//SI NO QUEDAN PORCIONES LLAMO A LAS ABAJAS
			printf("OSO: Despierto a las abejas.\n",i);
			sms.fuente++;
			sms.tipo=abeja;
			msgsnd(id_queue,(struct msgbuf*)&sms,size,0);
			i=0;
		};
	};
};
