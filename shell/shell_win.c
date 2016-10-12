#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <windows.h>



#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

DIR * cmd_dir;
int cant_comandos = 7;
char* lista_comandos[7];
char* directorio_comandos = "./comandos";

//typedef int BOOL;
//#define WINAPI __stdcall;

void intHandler(int sig) {
   (void) signal(SIGINT, SIG_DFL);
}

void imprimir_ayuda();

int ejecutar(char *comm, char *a1, char *a2, char **MC) {
	int i,leng,ret,error;
	
	for (i = 0; i < 7;i++){
		leng = strlen((MC[i])) ;
  		int ret = strncmp(comm, MC[i], leng);
		if (ret == 0) {
			switch (i){
				case 0 : // mkdir
				{	
					if(strlen(a1)) {

						BOOL  error=CreateDirectory(
						  a1,
						  NULL
						);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 1 argumento",comm);
					return 1;
				}
				case 1: //rmdir
				{
					if(strlen(a1)) {
						BOOL  error=RemoveDirectory(
							  a1
							);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 1 argumento",comm);
					return 1;
				}
				case 2: // rename
				{
	 				if(strlen(a1) && strlen(a2)) {
	 					BOOL error= MoveFile(
								  a1,
								  a2
								);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 2 argumentos",comm);
	    			return 1;
				}
				case 3: // copy
				{
 	 				if(strlen(a1) && strlen(a2)) {
 	 					BOOL error =  CopyFile(a1,a2,TRUE);

						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 2 argumentos",comm);
	    			return 1;
				}
				case 4: // time
				{
	 				SYSTEMTIME st;
	 				GetSystemTime(&st);
	 				printf("La hora del sistema es = %02d:%02d\n", st.wHour,st.wMinute);
					return 1;
				}	
	 			case 5: // help
				{
	 				imprimir_ayuda();
					return 1;
				}
  				case 6: // exit
				{
	 				return 0;
				}
			}
		}
	}
}

void imprimir_ayuda(){
	printf("\n--------------------------------------");
	printf("\nAyuda: \n");
	printf("--------------------------------------\n");
	if (cant_comandos == 0){
		
		printf("No hay comandos disponibles para ejecutar. Para ejecutar comandos, los mismos deben estar en la carpeta 'comandos', compilados y sin extension.\n\nTeclee 'exit' para salir\n ");
	}else{
		printf("La lista de comandos disponibles es:\n");
		int i = 0;
		for (i = 0; i < cant_comandos; i++){
			printf("%i) %s\n",i,lista_comandos[i]);
		}
	}

	printf("\n");
}

int filtrar_entrada(char caracter){
	if ( caracter == '\\' || caracter == '.' || caracter == '/' || (caracter >= '0' && caracter <= '9') || (caracter >= 'a' && caracter <= 'z' ) || (caracter >= 'A' && caracter <= 'Z' || caracter == ' ')){
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]){

	int termine=0;
	char caracter;
	int length=0; // cantidad de caracteres
	char* comando= (char*) calloc(100,sizeof(char*)); //comando
	char* arg1=(char*) calloc(100,sizeof(char*));//argumentos del comando
	char* arg2=(char*) calloc(100,sizeof(char*));//argumentos del comando
	int espacio=0;
	int iguales = -1;
	int espacio_activo = -1;

	// comandos aceptados
	char *cmd1 = "mkdir";
	char *cmd2 = "rmdir";
	char *cmd3 = "rename";
	char *cmd4 = "copy";
	char *cmd5 = "time";
	char *cmd6 = "help";
	char *cmd7 = "exit";

	strncat(cmd1, "\0", 1);
	strncat(cmd2, "\0", 1);
	strncat(cmd3, "\0", 1);
	strncat(cmd4, "\0", 1);
	strncat(cmd5, "\0", 1);
	strncat(cmd6, "\0", 1);
	strncat(cmd7, "\0", 1);

	lista_comandos[0] = cmd1;
	lista_comandos[1] = cmd2;
	lista_comandos[2] = cmd3;
	lista_comandos[3] = cmd4;
	lista_comandos[4] = cmd5;
	lista_comandos[5] = cmd6;
	lista_comandos[6] = cmd7;

	while(!termine){
			espacio = 0;
			espacio_activo = -1;
			iguales = -1;

			printf("[so_shell]$ ");
			caracter = getchar();

			if (filtrar_entrada(caracter)){
				while( caracter != '\n'){

					if (filtrar_entrada(caracter)){
						if(caracter == (unsigned char) ' ' || caracter == (unsigned char)'\t'){
							if (espacio_activo == 0){
								espacio++;
							}
							espacio_activo = 1;
						}else {
							espacio_activo = 0;
							if(espacio==0)
								strncat(comando,&caracter,1);
							else if(espacio==1)
								strncat(arg1,&caracter,1);
							else 
								strncat(arg2,&caracter,1);
							
						}
					}
					caracter = getchar();
				};

				strncat(comando,"\0",1);
				strncat(arg1,"\0",1);
				strncat(arg2,"\0",1);

				fflush(stdin);
				if (strlen(comando) > 0){
					if(strcmp(comando,"help") == 0){
						imprimir_ayuda();
					}else if(strcmp(comando,"exit") == 0){
						termine = 1;
					}else{
						
						/*printf("Comando leido %s \n",comando);
						printf("Tamaño comando leido por consola %i\n", strlen(comando));
						*/// Comparo con todos los comandos de la lista para saber cual es
						
						int i=0;
						int iguales = -1;
						while((iguales != 0) && (i <= cant_comandos - 1)){
							/*printf("Tamaño comando leido de lista %i\n", strlen(&lista_comandos[i]));
							printf("Comparando %s con %s\n",comando,&lista_comandos[i]);
							*/
							iguales = strcmp(comando,lista_comandos[i]);
							
							i++;
						};
						/*printf("Resultado de comparacion: %i\n",iguales);
						printf("i es igual a %i\n",i);
						*/
						i--;

						if(iguales == 0){
							ejecutar(comando,arg1,arg2,lista_comandos);
						}else{
							printf("Comando no encontrado\n");
						}
					}
				}
			}
			comando= (char*) calloc(100,sizeof(char*)); //comando
			arg1=(char*) calloc(100,sizeof(char*));//argumentos del comando
			arg2=(char*) calloc(100,sizeof(char*));//argumentos del comando

		}	
}