#include <stdio.h>
 #include <sys/stat.h>
       #include <sys/types.h>

/** asumo como máximo 3 argumentos (comando + 2 args)
	ya que ningún comando aceptado por la shell necesita más de 2 argumentos
	Comandos aceptados por la SHELL: 
		1- mkdir
		2- rmdir
		3- rename
		4- copy
		5- time
		6- help
		7- exit
*/

void cargarArgumentos(int n, char *tmpArgs, char *cmd, char* arg1, char *arg2);
int llamada(char *comm, char *a1, char *a2, char **MC);
int copy(char *dest, char *src); // una parte de esta funcion fue extraida de internet
void imprimirAyuda();
void liberar(char *tmpArgs, char *cmd, char* arg1, char *arg2);

int main(int argc, char *argv[]) {
	
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
	
	char c;
	int noTermine = 1;
	int cantArgs = 1;
	char *tmp = (char *)malloc(sizeof(char) * 100);
	char *cmd = (char *)malloc(sizeof(char) * 100);
	char *arg1 = (char *)malloc(sizeof(char) * 100);
	char *arg2 = (char *)malloc(sizeof(char) * 100);
	
	printf("***** Mini Shell - Proyecto SO *****\n\n");
	printf("Ingrese un comando o 'help' para obtener ayuda\n");
	fflush(stdout);
	
	while(noTermine) {
		c = getchar();
		printf("%c",c);
		switch(c) {
			case '\n': 
			{
				if(tmp[0] == '\0')
					printf("Mini Shell\n");
				else { 
					//printf("Cargo comando y argumentos\n");
					cargarArgumentos(cantArgs,tmp,cmd,arg1,arg2);
					//printf("Comando %s\n",cmd);
					noTermine = llamada(cmd,arg1,arg2,MisComandos);
					if(noTermine == 1) {
						// libero los comandos anteriores para cargar nuevos
						liberar(tmp,cmd,arg1,arg2);
						//free(tmp);
						//free(cmd);
						//free(arg1);
						//free(arg2);
						tmp = (char *)malloc(sizeof(char) * 100);
						cmd = (char *)malloc(sizeof(char) * 100);
						arg1 = (char *)malloc(sizeof(char) * 100);
						arg2 = (char *)malloc(sizeof(char) * 100);
						cantArgs = 1;
					}
				}
				break;
			}
			case ' ': // esto al final no se usa, pensaba contar la cantidad de argumentos pero no lo necesito, igual lo dejo
			{
				strncat(tmp, &c, 1);
				cantArgs++;
				if (cantArgs == 4) {
					printf("Superada la cantidad máxima de argumentos permitidos\n");
					printf("Por favor escriba 'help' seguido de ENTER para obtener ayuda\n");
					cantArgs = 0;
					free(tmp);
					tmp = (char *)malloc(sizeof(char) * 100);
				}
				break;
			}
			default:
			{
				strncat(tmp, &c, 1);
				break;
			}
		}
	}
	free(tmp);
	free(cmd);
	free(arg1);
	free(arg2);
	
	printf("\n");
	return 0;
}

void cargarArgumentos(int n, char *tmpArgs, char *cmd, char* arg1, char *arg2) {
	char *S = tmpArgs;
	int i = 0;
	char c = 'a';
	
	if(S[0] == ' ') {
		printf("Comando no encontrado\n");
		printf("Por favor escriba 'help' seguido de ENTER para obtener ayuda\n");
	}
	else {
		while(S[i] != ' ' && S[i] != '\n' && S[i] != '\0') { // comando
			c = S[i];
			if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z' ))
				strncat(cmd, &c, 1);
			i++;
		}
		if(S[i] == ' ') { // comando + 1 argumento
			i++;
			while(S[i] != ' ' && S[i] != '\n' && S[i] != '\0') { // 1 argumento
				c = S[i];
				if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z' ))
					strncat(arg1, &c, 1);
				i++;
			}
			if(S[i] == ' ') { // comando + 2 argumentos
				i++;
				while(S[i] != ' ' && S[i] != '\n' && S[i] != '\0') { // 2 argumento
					c = S[i];
					if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z' ))
						strncat(arg2, &c, 1);
					i++;
				}
			}
		}
	}
	strncat(cmd, "\0", 1);
	strncat(arg1, "\0", 1);
	strncat(arg2, "\0", 1);
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
						error = mkdir(a1, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
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
						error = rmdir (a1);
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
						error = rename (a1,a2);
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
						error = copy (a1,a2);
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

int copy(char *dest, char *src) {
	int fd_dest, fd_src;
	char buf[4096];
	ssize_t nread;
	
	fd_src = open(src, O_RDONLY);
	if (fd_src < 0) return (-1);

    fd_dest = open(dest, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_dest < 0) return (-1);

    while (nread = read(fd_src, buf, sizeof buf), nread > 0) {
		char *out_ptr = buf;
		ssize_t nwritten;
		
		do {
			nwritten = write(fd_dest, out_ptr, nread);
			if (nwritten >= 0) {
				nread -= nwritten;
				out_ptr += nwritten;
			}
			else if (nwritten < 0) {
				return (-1);
			}
		} while (nread > 0);
	}
	
	if (nread == 0) {
		if (close(fd_dest) < 0) {
			fd_dest = -1;
			return (-1);
		}
		close(fd_src);
		
		return 0;
	}
	return (-1);
}

void imprimirAyuda() {
	printf("Mini Shell\n");
	printf("Lista de comandos aceptados por la Mini Shell:\n");
	printf("1) mkdir arg1\n");
	printf("2) rmdir arg1\n");
	printf("3) rename arg1 arg2\n");
	printf("4) copy arg1 arg2\n");
	printf("5) time\n");
	printf("6) help\n");
	printf("7) exit\n");
	printf("Donde arg1 y arg2 corresponden a los argumentos que necesita cada comando\n");
}

void liberar(char *tmpArgs, char *cmd, char* arg1, char *arg2){
	int x;
	for(x = 0; x < 100; x++){
		tmpArgs[x] = NULL;
		cmd[x] = NULL;
		arg1[x] = NULL;
		arg2[x] = NULL;
	}
}