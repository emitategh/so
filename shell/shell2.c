#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>


#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

DIR * cmd_dir;
char** lista_comandos;
int cant_comandos = 0;
char* directorio_comandos = "./comandos";

void intHandler(int sig) {
   (void) signal(SIGINT, SIG_DFL);
}



int llamada(char *comm, char *a1, char *a2, char **MC) {
	int i,leng,ret,error;
	
	for (i = 0; i < 7;i++){
		leng = strlen((MC[i])) ;
  		int ret = strncmp(comm, MC[i], leng);
		if (ret == 0) {
			switch (i){
				case 0 : // mkdir
				{	
					if(a1[0] != '\n' || a1[0] != '\0') {

						BOOL  error=CreateDirectory(
						  _In_     LPCTSTR               a1,
						  _In_opt_ LPSECURITY_ATTRIBUTES NULL
						);
				//	error = mkdir(a1, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 1 argumento",comm);
					return 1;
				}
				case 1: //rmdir
				{
					if(a1[0] != '\n' || a1[0] != '\0') {
						BOOL  error=RemoveDirectory(
							  _In_ LPCTSTR a1
							);


						//error = rmdir (a1);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 1 argumento",comm);
					return 1;
				}
				case 2: // rename
				{
	 				if(a1[0] != '\n' || a1[0] != '\0' || a2[0] != '\n' || a2[0] != '\0') {
	 					BOOL error= MoveFile(
								  _In_ LPCTSTR a1,
								  _In_ LPCTSTR a2
								);
						//error = rename (a1,a2);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 2 argumentos",comm);
	    			return 1;
				}
				case 3: // copy
				{
 	 				if(a1[0] != '\n' || a1[0] != '\0' || a2[0] != '\n' || a2[0] != '\0') {
 	 					BOOL  CopyFile(
						  _In_ LPCTSTR a1,
						  _In_ LPCTSTR a2,
						  _In_ BOOL    NULL
						);

						//error = copy (a1,a2);
						if (error < 0)
							printf ("ERROR\n");
					}
					else
						printf("%s necesita 2 argumentos",comm);
	    			return 1;
				}
				case 4: // time
				{
	 				time_t seconds;
	 				seconds = time(NULL);
	 				printf("Horas desde el 1 de Enero de 1970 = %ld\n", seconds/3600);
					return 1;
				}	
	 			case 5: // help
				{
	 				imprimirAyuda();
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
		printf("%i) %s\n",i++,"help");
		printf("%i) %s\n",i++,"exit");
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
	char* comando= (char*) malloc(sizeof(char*)*100); //comando
	char* arg1=(char*) malloc(sizeof(char*)*100);//argumentos del comando
	char* arg2=(char*) malloc(sizeof(char*)*100);//argumentos del comando
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

	char *MisComandos[7] = {cmd1,cmd2,cmd3,cmd4,cmd5,cmd6,cmd7};

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

				//strncat(comando,"\0",1);
				//strncat(arg1,"\0",1);
				//strncat(arg2,"\0",1);

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
							ejecutar(comando,arg1,arg2,MisComandos);
						}else{
							printf("Comando no encontrado\n");
						}
					}
				}
			}
			comando= (char*) malloc(sizeof(char*)*100); //comando
			arg1=(char*) malloc(sizeof(char*)*100);//argumentos del comando
			arg2=(char*) malloc(sizeof(char*)*100);//argumentos del comando

		}	
}

