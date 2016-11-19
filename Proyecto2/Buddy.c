#include <stdio.h>

struct celda{
	int estado;
	int size;
	int ID;
	char pro;
	struct celda* siguiente;
	//struct celda* parcion_compañera; //ESTO ES PARA CUANDO LIBERO 
} *memoria;

#define OCUPADO 0
#define LIBRE 1
int cant=1;
//TODOS LOS TAMAÑOS DE LOS PROCESOS Y MEMORIA SERAN EN KB
int main(){
	memoria=(struct celda *)malloc(sizeof(struct celda));
	memoria->estado=LIBRE;
	memoria->siguiente=NULL;
	memoria->size=64*1024; // EN KB
	memoria->ID=1;
	memoria->pro='*';
	cant=1;
	printf("MEMORIA DE :%i KB\n",memoria->size);
	insertar('A',15360,memoria);
	insertar('B',43008,memoria);
	insertar('C',8192,memoria);
	insertar('D',8192,memoria);
	liberar('C');
	insertar('E',5120,memoria);
	recorrer(memoria);
};

void insertar(char id,int tam_pro,struct celda* particion){
	printf("\nEstoy por insertar el proceso: %c que ocupa:%i KB --- En una particion de: %i KB de capacidad\n",id,tam_pro,particion->size);
	int entro=0;
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	while((entro==0)&&(aux!=NULL)){
		//MIENTRAS NO ENTRO EL PROCESO Y PUEDA INGRESAR
		int tam_particion=aux->size;
		if(tam_pro>tam_particion)
			aux=aux->siguiente;
		else{
			//PUEDO ALOCARLO EN ESA PARTICION O EN UNA PARTICION "HIJA"
			while(entro==0){
				tam_particion=aux->size;
				if(aux->estado==OCUPADO)
					aux=(aux->siguiente);
				else{
					if((tam_pro>=(tam_particion/2))&&(tam_pro<=tam_particion)){
						//PUEDO ALOCARLO EN ESA PARTICION
						if(aux->estado==LIBRE){
							entro=1;
							aux->estado=OCUPADO;
							aux->pro=id;
							printf("--- Se aloco exitosamente el proceso: %c ---\n",id);
						}
						else aux=(aux->siguiente);
					}
					else{
						//TENGO QUE particionar
						printf("Hay que particionar la particion de: %i KB\n",tam_particion);
						struct celda* nueva=(struct celda *)malloc(sizeof(struct celda));
						cant++;
						nueva->size=tam_particion/2;
						nueva->siguiente=(aux->siguiente);
						nueva->ID=cant;
						nueva->estado=LIBRE;
						nueva->pro='*';

						aux->siguiente=nueva;
						aux->size=tam_particion/2;

						printf("Resultado de la particion: Particion:%i :%i KB --- Particion:%i : %i KB\n",aux->ID,aux->size,nueva->ID,nueva->size);
					}
				};
			};
		}
	};
	if(entro==0)
		//QUIERE DECIR QUE NO PODIA ALOCARSE
		printf("--- El Proceso:%c no puede alocarse ---\n",id);
};

void recorrer(struct celda* mem){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=mem;
	int suma=0;
	printf("\n--- Recorrido de la memoria --- \n*Particiones:\n");
	while(aux!=NULL){
		printf("\nParticion: %i :\n*Estado (Ocupado=0, Libre=1): %i\n*Tamaño:%i KB\n*Proceso: %c\n",aux->ID,aux->estado,aux->size,aux->pro);
		if(aux->estado==LIBRE)
			suma=suma+(aux->size);
		aux=(aux->siguiente);
	};
	printf("\n*Fracmentacion externa:%i KB\n\n",suma);
}
void liberar(char id){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int encontre=0;
	char proceso;
	printf("---------- ESTOY POR BORRAR, MI DIRECCION DE MEMORIA ES:%p-----------------------\n",memoria);
	while(encontre==0){
		proceso=(aux->pro);
		if(proceso==id){
			encontre=1;
			aux->estado=LIBRE;
			aux->pro='*';
			printf("--- Se elimino exitosamente el Proceso: %c ---\n",id);
		}
		else 
			aux=(aux->siguiente);
	}
	if(encontre==0)
		printf("--- No existe el Proceso: %c ---\n",id);
}
//PARA LA LIBERACION DE MEMORIA COMO ES????