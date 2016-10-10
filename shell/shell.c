#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <curses.h>

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

DIR * cmd_dir;
char** lista_comandos;
int cant_comandos = 0;
char* directorio_comandos = "./comandos";
WINDOW *my_win;
int scr_x = 0;
int scr_y = 0;
char* shell_str = "[so_shell]$ ";
int char_buffer_size = 100;
char* filtered_buffer;

void ini_array(char* array){

}


void ejecutar(char* cmd,char* ar1,char* ar2){
	char* args_cmd[] = {cmd,ar1,ar2,(char *)0};
	int pid = fork();
	
	if (pid == 0){
		char * cmd_exec = (char * ) malloc(sizeof(char*)*char_buffer_size);
		strcat(cmd_exec,directorio_comandos);
		strcat(cmd_exec,PATH_SEPARATOR);
		strcat(cmd_exec,cmd);
		execv(cmd_exec,args_cmd);

        exit(127); /* only if execv fails */
	}else{
		wait(NULL);
		getyx(stdscr,scr_y,scr_x);
		printw("\n  "); // ?? con eso recupero el cursor a la posicion x= 0 en linea siguiente
		refresh();
		wmove(stdscr,scr_y,0);
	}
}

void imprimir_ayuda(){
	printw("----- Aliuuudaaaaaa SO Mini Shell ------\n");
	printw("La lista de comandos disponibles es:\n");
	for (int i = 0; i < cant_comandos; i++){
		printw("%i) %s\n",i,lista_comandos[i]);
	}

	printw("\n");
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

int filtrar_entrada(int caracter){
	char c = (char) caracter;
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z' )){
		return 1;
	}
	
	return 0;
}

void del_char_from_str(char** string){
	char *aux = (char*) malloc(sizeof(char*)*char_buffer_size);
	memmove(aux,*string,strlen(*string)-1);
	strncat(aux,"\0",1);
	*string = (char*) malloc(sizeof(char*)*char_buffer_size);
	memmove(*string,aux,strlen(aux));
}

void auto_complete(){
	
}

void manejar_buffer(){
	filtered_buffer = (char*) malloc(sizeof(char*)*char_buffer_size);
	int caracter;
	int last_char_pos = 0;
	while ((caracter = getch()) != '\n') {
		printw("Keycode: %d ", caracter);
		getyx(stdscr,scr_y,scr_x);
		if (last_char_pos < scr_x){
			last_char_pos = scr_x;
		}
        switch (caracter) {
	        case 127: //backspace
	            if ((scr_x - 1) >= strlen(shell_str)){
		            if (wmove(stdscr,scr_y, scr_x - 1) != ERR) {
		        		delch();
		        		del_char_from_str(&filtered_buffer);
		            }else{
		            	printw("no se pudo borrar\n");
		            }
	            }
	            break;
	        /*case 260 :
	        	if ((scr_x - 1) >= strlen(shell_str)){
		        	wmove(stdscr,scr_y,scr_x-1);
		        }
	        	break;
	        case 261:
	        	if (scr_x < last_char_pos){
	        		wmove(stdscr,scr_y,scr_x+1);
	        	}
	        	break;*/
	        case 9: //tab
	        	auto_complete();
	        	break;
	        default:

	            if (filtrar_entrada(caracter)){
					addch(caracter);
					char c = (char)caracter;
					strncat(filtered_buffer,&c,1);
				}
	            break;
        }

		refresh ();
    }
    strcat(filtered_buffer,"\0");
}

int main(int argc, char *argv[]){

	int termine=0;
	
	int length=0; // cantidad de caracteres
	char* comando= (char*) malloc(sizeof(char*)*char_buffer_size); //comando
	char* arg1=(char*) malloc(sizeof(char*)*char_buffer_size);//argumentos del comando
	char* arg2=(char*) malloc(sizeof(char*)*char_buffer_size);//argumentos del comando
	int espacio=0;
	int iguales = -1;
	char caracter;
	cmd_dir = opendir(directorio_comandos);
	initscr();
	noecho();
	if (cmd_dir)
  	{
	  	buscar_comandos();
		if (cant_comandos == 0){
			printw("No hay comandos disponibles para ejecutar\n");
		}else{
			
			//cbreak();
			keypad(stdscr, TRUE);
			while(!termine){
				getyx(stdscr,scr_y,scr_x);
				//printw("");
				//printw("y: %i x: %i \n",scr_y,scr_x);
				//wmove(stdscr,scr_y+1,0);
				printw(shell_str);
				refresh();
				manejar_buffer();

				int i = 0;

				while (filtered_buffer[i] != '\0') {
					//printw("Keycode: %d ", caracter);
					caracter = filtered_buffer[i++];
			        
				       
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
				
			    //printw("comando : %s\n",comando);
				
			    printw("\n");
				strncat(comando,"\0",1);
				strncat(arg1,"\0",1);
				strncat(arg2,"\0",1);

				getyx(stdscr,scr_y,scr_x);
				move(scr_y,0);
				refresh();

				fflush(stdin);
				if (strlen(comando) > 0){
					if(strcmp(comando,"help") == 0){
						imprimir_ayuda();
					}else if(strcmp(comando,"exit") == 0){
						termine = 1;
					}else{
						
					
						espacio=0;
						/*printw("Comando leido %s \n",comando);
						printw("Tamaño comando leido por consola %i\n", strlen(comando));
						*/// Comparo con todos los comandos de la lista para saber cual es
						
						int i=0;
						int iguales = -1;
						while((iguales != 0) && (i <= cant_comandos - 1)){
							/*printw("Tamaño comando leido de lista %i\n", strlen(&lista_comandos[i]));
							printw("Comparando %s con %s\n",comando,&lista_comandos[i]);
							*/
							iguales = strcmp(comando,lista_comandos[i]);
							
							i++;
						};
						/*printw("Resultado de comparacion: %i\n",iguales);
						printw("i es igual a %i\n",i);
						*/
						i--;
						if(iguales == 0){
							ejecutar(comando,arg1,arg2);
							//move(scr_y+1,0);
						}else{
							printw("Comando no encontrado\n");
							
						}
					}
				}

				comando= (char*) malloc(sizeof(char*)*char_buffer_size); //comando
				arg1=(char*) malloc(sizeof(char*)*char_buffer_size);//argumentos del comando
				arg2=(char*) malloc(sizeof(char*)*char_buffer_size);//argumentos del comando

			}
		}
		closedir(cmd_dir);
	}else{
	  printw("No se pudo abrir el directorio de comandos\n");
	}
	
	endwin();
}