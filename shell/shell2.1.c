#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
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



void ejecutar(char* cmd,char* ar1,char* ar2){
	//int link[2];
	char child_input_buffer[4096];
	int args_index = 1;
	// pipes http://tldp.org/LDP/lpg/node11.html
	//if (pipe(link)==-1)
    //	exit(EXIT_FAILURE);
    	//die("pipe");

	int pid = fork();	
	if (pid == 0){

		char * cmd_exec = (char * ) malloc(sizeof(char*)*100);
		strcat(cmd_exec,directorio_comandos);
		strcat(cmd_exec,PATH_SEPARATOR);
		strcat(cmd_exec,cmd);

		char* args_cmd[3];

		args_cmd[0] = malloc(sizeof(strlen(cmd)));
		args_cmd[1] = malloc(sizeof(strlen(ar1)));
		args_cmd[2] = malloc(sizeof(strlen(ar2)));

		args_cmd[0] = cmd;
		if (strlen(ar1) > 0){
			args_cmd[args_index] = ar1;
			args_index++;
		}

		if (strlen(ar2) > 0){
			args_cmd[args_index] = ar2;
			args_index++;
		}
		args_cmd[args_index++] = (char *)0;
		
		
	    //close(link[0]); // 0 reading
	    //close(link[1]);	// 1 writing
	//	dup2 (0,link[0]);// STDOUT_FILENO); // connect pipe from execl to stdin
		//execl(cmd_exec,cmd,args_cmd,(char *)0);


		execv(cmd_exec,args_cmd);
        exit(127); /* only if execv fails */
	}else{
		
		/*close(link[1]); // si queremos recibir datos del hijo, entonces tenemos q cerrar 1
		int nbytes = read(link[0], child_input_buffer, sizeof(child_input_buffer));
		printf("Leidos %i bytes\n", nbytes);
    	printf("Output: (%.*s)\n", nbytes, child_input_buffer);
		
		/*while( scanf( "%s", child_input_buffer ) != EOF )
        {
	    	printf("%s", child_input_buffer);
	 	}*/
		wait(NULL);
		printf("\n");
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
		lista_comandos = (char**) malloc(sizeof(char*)*cant_comandos);
	    
	    	
	    while ((file = readdir(cmd_dir)) != NULL)
	    {
	    	char * filename = file->d_name;
	    	//printw("filename %s\n",file->d_name);

	    	if ((file->d_type == DT_REG) && (has_extension(filename) != 0) )
			{
	    		lista_comandos[i] = (char*) malloc(sizeof(char)*strlen(filename));
				strcpy(lista_comandos[i], filename);
				i++;
			}
	    }
    }
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

	//signal(SIGINT, intHandler);

	cmd_dir = opendir(directorio_comandos);
	if (cmd_dir)
  	{
	  	buscar_comandos();
		if (cant_comandos == 0){
			printf("No hay comandos disponibles para ejecutar\n");
		}else{
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