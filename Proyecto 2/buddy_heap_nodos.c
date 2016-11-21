#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LLENO 0 // 
#define OCUPADO 1 // Tiene uno de los hijos llenos
#define LIBRE 2 // Ambos hijos libres
#define SO *

time_t t;

typedef struct proceso{
	int id;
	int size;
} proc, *pproc;

typedef struct memoria_celda{

	int estado;
	int size;
	int disponible;
	int cantidad;
	pproc elem;
	char pro;
	struct memoria_celda* hijo_d;
	struct memoria_celda* hijo_i;
	struct memoria_celda* padre;
} *memoria, *pmemoria;


int insertar();
int liberar();
void compacta_memoria();
pmemoria crear_celda();
int rand_range(int min_n, int max_n);
void darRequerimientos(int n,memoria mem);


int main(){
	printf("\nAlgoritmo Buddy, Proyecto 2\n");
	pmemoria mem = (pmemoria) malloc(sizeof(struct memoria_celda));
	int capacidad = 16348;
	printf("\nCapacidad de memoria: %i\n", capacidad);
	srand((unsigned)time(&t));

	mem->size = capacidad;
	mem->disponible = capacidad;
	mem->cantidad = 0;
	mem->estado = LIBRE;
	mem->hijo_d = NULL;
	mem->hijo_i = NULL;
	mem->padre = NULL;
	mem->elem = NULL;
	mem->pro = '*';

	darRequerimientos(5,mem);

}

//si soy mayor a la mitad de la locacion, la ocupo
//sino divido y aksjd
int insertar(pproc proceso,pmemoria locacion, int nivel){
	printf("En insertar\n");
	int tamanio_locacion = locacion->size;
	int result = 0;

	if (proceso->size < locacion->disponible){
		// Soy hoja?
		if (locacion->hijo_i == NULL && locacion->hijo_d == NULL){
			if (locacion->estado == LIBRE){
				if (proceso->size < tamanio_locacion/2){
					printf("Divido nodo de tamaño %i e intento por izquierda a nivel %i\n",locacion->size, nivel+1);
					locacion->hijo_d = crear_celda(tamanio_locacion/2, locacion);
					locacion->hijo_i = crear_celda(tamanio_locacion/2, locacion);
					
					result  = insertar(proceso,locacion->hijo_i,nivel+1);
					if (result == 0){
						printf("No pude por izquierda, voy por derecha, a nivel %i\n",nivel +1);
						result = insertar(proceso,locacion->hijo_d,nivel+1);
					}
					
				}else{
					locacion->elem = proceso;
					locacion->estado = OCUPADO;
					if (locacion->padre != NULL){
						locacion->padre->estado = OCUPADO;
						if (locacion->padre->hijo_d == locacion){
							locacion->padre->estado = LLENO;
						}
					}
					printf("Inserte proceso: %i, con size %i, en nodo de tamaño %i, en nivel %i\n",proceso->id,proceso->size,locacion->size, nivel);
					return 1;
				}
			}	
		}else{
			
			if (proceso->size < tamanio_locacion/2){
				// me voy para la izquierda
				pmemoria hijo = locacion->hijo_i;

				if (hijo->estado != LLENO){
					result = insertar(proceso,locacion->hijo_i,nivel+1);
					printf("Voy por izquierda, a nivel %i\n",nivel +1);
					if (result == 0){
						printf("NO PUDE INSERTAR EN IZQUIERDO, voy a derecha a nivel %i\n",nivel +1);
						result = insertar(proceso,locacion->hijo_d,nivel+1);
					}
				}else{
					printf("Hijo Izquierdo LLENO intento por derecha a nivel %i\n",nivel+1);
					if (locacion->hijo_d->estado != LLENO){

						if (locacion->hijo_d->estado == LIBRE){
							result = insertar(proceso,locacion->hijo_d,nivel+1);
						}else{
							// Esta ocupado, no lleno pero no libre
							if (proceso->size < locacion->hijo_d->size/2){
								printf("Voy por derecha, a nivel %i\n",nivel +1);
								result = insertar(proceso,locacion->hijo_d,nivel+1);
							}else{
								printf("El lugar esta ocupado o su tamaño no es suficiente. tengo q volver hasta el primer camino libre\n");
								result = 0;
							}
						}
					}else{
						result = 0;
						printf("No se pudo insertar,camino ocupado\n");
					}
				}
			}else{
				printf("No se pudo insertar el proceso %i (size %i). ",proceso->id,proceso->size);
				printf("Tamaño disponible en celda: %i\n",tamanio_locacion/2);
			}
		}

		if (result == 1){
			if (locacion->estado == LIBRE){
				locacion->estado = OCUPADO;
				locacion->disponible -= proceso->size;
			}
		}

		if (nivel == 0 && result == 1){
			locacion->cantidad++;
			locacion->disponible -= proceso->size;
		}

	}else{
		printf("Locacion con memoria insuficiente\n");
		printf("Disponible %i\n",locacion->disponible);
		printf("Requerido %i\n", proceso->size);
	}
	
	return result;
	
}

int liberar(pproc proceso,pmemoria locacion,int nivel){
	int tamanio_locacion = locacion->size;
	int result = 0;
	// Soy hoja?
	if (locacion->hijo_i == NULL && locacion->hijo_d == NULL){
		if (locacion->estado == OCUPADO){
			if ((locacion->elem)->id == proceso->id){
				printf("Encontre proceso %i en nivel %i, en lado ",proceso->id,nivel );
				locacion->elem = NULL;
				locacion->estado = LIBRE;
				printf(", Liberado\n");
				result = 1;

			}
		}else{
			if (locacion->estado == LIBRE){
				printf("Locacion estado LIBRE\n");
				
			}else if (locacion->estado == LLENO){
				printf("Locacion estado LLENO\n");
			}
		}
	}else{
		if (proceso->size < tamanio_locacion/2){
			// me voy para la izquierda
			pmemoria hijo = locacion->hijo_i;

			if (hijo->estado != LIBRE){
				printf("Intento por izquierda a nivel %i\n",nivel+1);
				result = liberar(proceso,locacion->hijo_i,nivel+1);
				if (result == 0){
					printf("No lo encontre por izquierda, voy por derecha a nivel %i\n",nivel+1);
					result = liberar(proceso,locacion->hijo_d,nivel+1);
				}
			}else{
				printf("Hijo izquierdo Libre en nivel %i\n",nivel);
				if (locacion->hijo_d->estado != LIBRE){
					printf("Hijo derecjo OCUPADO, voy a nivel %i\n",nivel +1 );
					result = liberar(proceso,locacion->hijo_d,nivel+1);
				}else{
					printf("Hijo derecho Libre en nivel %i\n",nivel);
					result = 0;
				}
			}
		}else{
			
		}

		if (locacion->hijo_i != NULL && locacion->hijo_d != NULL){
			
			if ((locacion->hijo_i)->estado == LIBRE && (locacion->hijo_d)->estado == LIBRE){
				printf("Encontre CELDA para compactar en nivel %i\n",nivel);
				
				compacta_memoria(locacion);
			}else{
				if((locacion->hijo_i)->estado == LLENO){
					printf("Hijo izquierdo, estado LLENO \n");
				}else if((locacion->hijo_i)->estado == OCUPADO){
					printf("Hijo izquierdo, estado OCUPADO \n");
				}
				if((locacion->hijo_d)->estado == LLENO){
					printf("Hijo derecho, estado LLENO \n");
				}else if((locacion->hijo_d)->estado == OCUPADO){
					printf("Hijo derecho, estado OCUPADO \n");
				}
			}
		}

	}

	return result;
}

void compacta_memoria(pmemoria locacion){
	printf("Compactando...\n");
	free(locacion->hijo_i);
	free(locacion->hijo_d);
	free(locacion->elem);

	locacion->estado = LIBRE;
	locacion->elem = NULL;
	locacion->hijo_d = NULL;
	locacion->hijo_i = NULL;
}


pmemoria crear_celda(int size,pmemoria padre){
	pmemoria nuevo_hijo = (pmemoria) malloc(sizeof(struct memoria_celda));
	nuevo_hijo->size = size;
	nuevo_hijo->disponible = size;
	nuevo_hijo->cantidad = 0;
	nuevo_hijo->estado = LIBRE;
	nuevo_hijo->hijo_d = NULL;
	nuevo_hijo->hijo_i = NULL;
	nuevo_hijo->padre = padre;
	nuevo_hijo->elem = NULL;
	nuevo_hijo->pro = '*';

	return nuevo_hijo;
}


int rand_range(int min_n, int max_n){
    return rand() % (max_n - min_n + 1) + min_n;
};


void darRequerimientos(int n,memoria mem){
	int cont=0;
	int i=0;
	time_t t;
   	int size;
   	int r;
   	int insertados = 0;

   	pproc pool_procesos[n];
   //	srand((unsigned) time(&t));
	printf("\n----------------------- DAR REQUERIMIENTOS ----------------------- \n\n");
	while(i!=n){
		r= rand() % 2;
		if(r==0){
			//ELIJO UN PROCESO AL AZAR PARA LIBERAR
			if (insertados > 0){
				int victima=rand()%insertados;
				printf("Liberando proceso %i\n",pool_procesos[victima]->id);
				if (liberar(pool_procesos[victima],mem,0)){
					insertados--;
					
				}
			}
		}
		else{
			//CREO NUEVOS REQUERIMIENTOS
			size=rand_range(100,mem->size);
			
			pproc nuevo_proc = (pproc) malloc(sizeof(struct proceso));
			nuevo_proc->id = i;
			nuevo_proc->size = size;

			printf("Insertando proceso ID: %i (size %i)\n",nuevo_proc->id,nuevo_proc->size);
			if (insertar(nuevo_proc,mem,0)){
				pool_procesos[i] = nuevo_proc;
				insertados++;
			}

			printf("\nMemoria disponible luego de insercion %i \n\n",mem->disponible);
		}
		i++;
	};
};
