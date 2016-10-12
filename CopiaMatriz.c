#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/mman.h>

#include <time.h>
#include <sys/wait.h>

static int ** matrizResultado;

//ayuda es un proceso que se ejecutara cuando el usuario necesito soporte
void ayuda(){
	printf("Me parece que te falto el argumento. El tamaño de la matriz\n");
}

int ** construirMatriz(int n){
	printf("Construir Matriz\n");
	int i;
	int j;
	int ** matriz =  malloc(n*sizeof(int*));

	for(i=0; i<n;i++){
		matriz[i] = malloc(n*sizeof(int));
	}

	return matriz;
}

void inicializarMatriz(int** matriz, int n){
	printf("Inicializar Matriz\n");
	int i;
	int j;
	int * indice;
	int * subindice;
	int num = 0;
	for(i=0; i<n;i++){
		//printf("%i - %p\n",i, matriz[i]); 
		for(j=0; j<n;j++){
			indice = matriz[i];
			subindice = indice+j;
			//*subindice = rand() % 10;
			*subindice = num++;
		}
	}
}

void mostrarMatriz(int** matriz,int n){
	printf("Mostrar Matriz\n");
	
	int * indice;
	int * subindice;
	int i;
	int j;

	for (i=0;i<n;i++){
		for(j=0; j<n;j++){
			indice = matriz[i];
			subindice = indice+j;
			//printf("I:%i - J:%i - valor:%i\n",i,j, *(subindice));
			//printf("Direccion:%p\n", (subindice));
			printf(" %i ", *(subindice));
		}
		printf("\n");
	}
};

void multiplicarMatriz(int** matrizA,int** matrizB, int** matrizResultado,int n){


	printf("Multiplicar Matriz\n");
	printf("%p\n", matrizResultado);
	int i;
	int j;
	int * indiceA;
	int * indiceB;
	int * indiceR;
	int * subindiceA;
	int * subindiceB;
	int * subindiceR;
	int pid = -1;
	printf("Direccion de Resultado en el padre: %p\n",matrizResultado);
	for (i=0;i<n;i++){
		
		pid = fork();
		
		if (pid == 0){
			printf("PID = %i ---- PPID = %i\n", getpid(),getppid());
			//printf("Direccion de Resultado en el hijo: %p\n",matrizResultado);
			for(j=0; j<n;j++){
				indiceR = matrizResultado[j];
				subindiceR = indiceR + i;
				for(int k=0;k<n;k++){

					indiceA = matrizA[k];
					subindiceA = indiceA + i ;
					
					indiceB = matrizB[j];
					subindiceB = indiceB + k;
					
					*(subindiceR) += *subindiceA * (*subindiceB);
					
				}
				//printf("subindiceA:%i * subindiceB:%i\n",*subindiceA,*subindiceB);
				//printf("Multiplicacion: %i\n",*subindiceR);
				//printf("Direccion Multiplicacion: %p\n",subindiceR);
			}

		exit(EXIT_SUCCESS);
		}
	}

	if (pid > 0){
		int j = 0;
		while(wait(NULL) > 0){
			j++;
			printf("Termino %i\n",j);	
		}
			
		printf("Me clavo esperando...\n");
		//printf("Direccion de Resultado antes de mostrar: %p\n",matrizResultado);
		mostrarMatriz(matrizResultado,n);
	}

};

//argc son la cantidad de argumentos que se deben cargar;
//argv son los argumentos almacenados en un arreglo de caracteres;

int main(int argc, char* argv[]){
	
	if(argc < 2){
		ayuda();
	}
	else{
		int n = atoi(argv[1]); //obtenemos el tamaño de la matriz
		
		int seed = time(NULL);
		srand(seed);
		printf("Principal PID = %i\n", getpid());

		int** matrizA = construirMatriz(n); 
		inicializarMatriz(matrizA,n);
		mostrarMatriz(matrizA,n);
		int** matrizB = construirMatriz(n); 
		inicializarMatriz(matrizB,n);
		mostrarMatriz(matrizB,n);
		
		matrizResultado = mmap(0,  n * sizeof(int*), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

		printf("%p\n", matrizResultado);

		int i;
		for(i=0; i<n;i++){
			matrizResultado[i] = mmap(0, n * sizeof(int), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		}

		//inicializarMatriz(matrizResultado,n);

		printf("·················· RESULTADO ·······················\n");
		//mostrarMatriz(matrizResultado,n);		
		multiplicarMatriz(matrizA,matrizB,matrizResultado,n);
	}
}