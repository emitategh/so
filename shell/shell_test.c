#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void ejecutar(int i,char* ar1,char* ar2){
	
}

int main(int argc, char *argv[]){

	int termine=0;
	char caracter;
	int length=0; // cantidad de caracteres
	char* comando= (char*) malloc(sizeof(char*)*100); //comando
	char* arg1=(char*) malloc(sizeof(char*)*100);//argumentos del comando
	char* arg2=(char*) malloc(sizeof(char*)*100);//argumentos del comando
	int espacio=0;
	char* lista_comandos[7]={"mkdir","rmdir","rename","copy","time","help","exit"};


	while(!termine){

		scanf("%c",&caracter);

		while(caracter!='\n'){


			if(caracter!=' '){

				if(espacio==0)
					strncat(comando,&caracter,1);
				else if(espacio==1)
					strncat(arg1,&caracter,1);
					else 
						strncat(arg2,&caracter,1);
				
			}else {
				espacio++;
			}
		};
		espacio=0;


		// Comparo con todos los comandos de la lista para saber cual es
		int salir=0;
		int i=0;
		while((!salir)&&(i!=6)){
			
			int iguales=strcmp(comando,lista_comandos[i]);
			if(iguales)
				salir=1;
			i++;
		};
		
		if((i==6)&&(iguales)){
			termine=1;
		}else{
			if(iguales){
				ejecutar(comando,arg1,arg2);
			}
			else 
				imprimir_ayuda();
		}
	}
	
}