#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

DIR * cmd_dir;
char* lista_comandos;
int cant_comandos = 0;
char* directorio_comandos = "./comandos";


void ejecutar(char* cmd,char* ar1,char* ar2){
	char* args_cmd[] = {cmd,ar1,ar2,(char *)0};
	int pid = fork();
	
	if (pid == 0){
		char * cmd_exec = (char * ) malloc(sizeof(char*)*100);
		strcat(cmd_exec,directorio_comandos);
		strcat(cmd_exec,PATH_SEPARATOR);
		strcat(cmd_exec,cmd);
		execv(cmd_exec,args_cmd);

        exit(127); /* only if execv fails */
	}else{
		wait(NULL);
	}
}

void imprimir_ayuda(){
	printf("----- Aliuuudaaaaaa ------\n");
	printf("La lista de comandos disponibles es:\n");
	for (int i = 0; i < cant_comandos; i++){
		printf("%i) %s\n",i,&lista_comandos[i]);
	}
	
	
}

int has_extension(char * filename){
	int i = 0;
	while(filename[i] != '\0'){
		if (filename[i] == '.'){
			return 0;
		}
		i++;
	}
	return 1;
}

void buscar_comandos(){
  struct dirent *file;
  
	while ((file = readdir(cmd_dir)) != NULL)
    {
    	char * filename = file->d_name;
    	
    	if ((file->d_type == DT_REG) && (has_extension(filename) != 0) )
		{
			cant_comandos++;
		}

    }
    if (cant_comandos > 0){
	   	
    	rewinddir(cmd_dir);
		int i = 0;
	    
	    lista_comandos = malloc(cant_comandos*sizeof(char*));
	    while ((file = readdir(cmd_dir)) != NULL)
	    {
	    	char * filename = file->d_name;
	    	if ((file->d_type == DT_REG) && (has_extension(filename) != 0) )
			{
				strcpy(&lista_comandos[i], filename);
				i++;
			}
	    }
    	
    }
}

int filtrar_entrada(char caracter){
	if (caracter > 64 && caracter < 91 || caracter > 96 && caracter < 123 ) {
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

	cmd_dir = opendir(directorio_comandos);
	if (cmd_dir)
  	{
	  	buscar_comandos();
		if (cant_comandos == 0){
			printf("No hay comandos disponibles para ejecutar\n");
		}else{
			while(!termine){
				printf("[so_shell]$ ");
				caracter = getchar();

				if (filtrar_entrada(caracter)){
					while( caracter != '\n'){

						if (filtrar_entrada(caracter)){
							if(caracter != ' '){
								if(espacio==0)
									strncat(comando,&caracter,1);
								else if(espacio==1)
									strncat(arg1,&caracter,1);
								else 
									strncat(arg2,&caracter,1);
								
							}else {
								espacio++;
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
							
						
							espacio=0;
							/*printf("Comando leido %s \n",comando);
							printf("Tamaño comando leido por consola %i\n", strlen(comando));
							*/// Comparo con todos los comandos de la lista para saber cual es
							
							int i=0;
							int iguales = -1;
							while((iguales != 0) && (i <= cant_comandos - 1)){
								/*printf("Tamaño comando leido de lista %i\n", strlen(&lista_comandos[i]));
								printf("Comparando %s con %s\n",comando,&lista_comandos[i]);
								*/
								iguales = strcmp(comando,&lista_comandos[i]);
								
								i++;
							};
							/*printf("Resultado de comparacion: %i\n",iguales);
							printf("i es igual a %i\n",i);
							*/
							i--;
							if(iguales == 0){
								ejecutar(comando,arg1,arg2);
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
		closedir(cmd_dir);
	}else{
	  printf("No se pudo abrir el directorio de comandos\n");
	}
	
}