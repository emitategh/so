#include <stdio.h>
#include <stdlib.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <string.h> 
#include <sys/stat.h>



void imprimir_ayuda(){
	printf("\n--------------------------------------");
	printf("\nAyuda: \n");
	printf("--------------------------------------\n");
	
		
	printf("Los permisos deben ser numeros enteros, UGO. Ej: 775\n ");
	
	printf("\n");
}


/*
	S_IRWXU
	read, write, execute/search by owner
	S_IRUSR
	read permission, owner
	S_IWUSR
	write permission, owner
	S_IXUSR
	execute/search permission, owner
	S_IRWXG
	read, write, execute/search by group
	S_IRGRP
	read permission, group
	S_IWGRP
	write permission, group
	S_IXGRP
	execute/search permission, group
	S_IRWXO
	read, write, execute/search by others
	S_IROTH
	read permission, others
	S_IWOTH
	write permission, others
	S_IXOTH
	execute/search permission, others
*/

int int_to_binary(int n){
	
	char * num = (char *) malloc(sizeof(char)*3);
    int lugar = 0;
    while(n){
    	if (n & 1){
    		num[lugar] = '1';
    	}else{
    		num[lugar] = '0';
    	}
    	n >>= 1;
    	lugar++;
    }

    printf(": %s\n",num);
    return strtol(num,NULL,10);
}


int main(int argc, char *argv[]){

	char file[500];
	long conv;
	int permission;
	char *p;

	if (argc > 2 ){
		
		strcpy(file,argv[2]);
		if (strlen(file) > 0){
			errno = 0;

			conv = strtol(argv[1], NULL, 10);
			if (errno != 0 || conv > INT_MAX) {
				imprimir_ayuda();
			} else {
			    permission = conv;    
			   

				int user_p = (permission / 100)*64;
			    printf("User: %i\n",user_p);

			    int group_p = (int)((permission/10)%10)*8;
			    printf("Group: %i\n",group_p );
			    
			    int others_p = (int)(permission%10);
			    printf("Others: %i\n",others_p );

			    int new_permission = user_p|group_p|others_p;
			    /*
			    int n = new_permission;
			    while(n){
			    	if (n & 1){
			    		printf("1");
			    	}else{
			    		printf("0");
			    	}
			    	n >>= 1;
			    }
			    printf("\n");
			    */
			    errno = 0;
			    int ch  = chmod(file, new_permission);
			    
			    printf("Permission: %d\n", permission);
			    printf("Result: %i\n",ch);
			    printf("errno: %i\n",errno);
			    //int results[9] = {EACCES,ELOOP,ENAMETOOLONG,ENOTDIR,ENOENT,EPERM,EROFS,EINTR,EINVAL};
			    switch(errno){
					case EACCES:
						printf("Permiso denegado\n");
						break;
					case ELOOP:
						printf("Existe un loop en un simbolico del path\n");
						break;
					case ENAMETOOLONG:
						printf("Path demasiado largo\n");
						break;
					case ENOTDIR:
						printf("Path no es un directorio\n");
						break;
					case ENOENT:
						printf("Archivo inexistente o path vacio\n");
						break;
					case EPERM:
						printf("No tienes privilegios\n");
						break;
					case EROFS:
						printf("Archivo o directorio solo lectura\n");
						break;
					case EINTR:
						printf("Error \n");
						break;
					case EINVAL:
						printf("Permisos invalidos\n");
						break;
			    }
			   	if (ch >= 0){
			   		printf("Exitoouu al intentar cambiar permisos\n");
			   	}else{
			   		printf("Error al intentar cambiar permisos\n");
			   	}
			}
		}


	}

	return 0;
}