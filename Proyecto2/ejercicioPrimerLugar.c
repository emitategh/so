#include <stdio.h>

struct celda{
	int estado;
	int size;
	int ID;
	int pro;
	struct celda* siguiente;
	struct celda* anterior;
	
	//struct celda* parcion_compañera; //ESTO ES PARA CUANDO LIBERO 
} *memoria;

#define OCUPADO 0
#define LIBRE 1
#define SO *

int cant; //SERA EL IDENTIFICADOR DE LAS PARTICIONES
//TODOS LOS TAMAÑOS DE LOS PROCESOS Y MEMORIA SERAN EN KB
int main(){
	memoria=(struct celda *)malloc(sizeof(struct celda));
	memoria->size=65536;
	memoria->estado=LIBRE;
	memoria->siguiente=NULL;
	memoria->anterior=NULL;
	memoria->ID=0;
	memoria->pro=-1;
	cant=1;
	printf("MEMORIA DE :%i KB\n",memoria->size);
	insertar(1,15360);
	insertar(2,15360);
	insertar(3,15360);
	recorrer();
	liberar(4);
	insertar(5,8192);
	recorrer();
};

void insertar(int id,int tam_pro){
	printf("Estoy por insertar el Proceso: %i DE :%i KB\n",id,tam_pro);
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int entro=0;
	int tam_particion;
	while((entro==0)&&(aux!=NULL)){
		tam_particion=aux->size;
		if((aux->estado==LIBRE)&&(tam_particion>=tam_pro)){
			struct celda* nueva=(struct celda *)malloc(sizeof(struct celda));
			nueva->ID=cant;
			nueva->estado=OCUPADO;
			nueva->siguiente=aux;
			nueva->size=tam_pro;
			nueva->anterior=(aux->anterior);
			nueva->pro=id;
			if((aux->anterior)!=NULL){
				(aux->anterior)->siguiente=nueva;
				 //MEDIO CHANCHO, ESTO ES EN CASO DE SER EL PRIMER PROCESO EN USAR LA MEMORIA SE MODIFIQUE EL PUNTERO
			}
			else{
				printf("CAMBIE EL PUNTERO\n");
				memoria=nueva;
			}

			aux->size=tam_particion-tam_pro;
			aux->anterior=nueva;
			entro=1;
			cant++;
		}
		else 
			aux=(aux->siguiente);
	}
	if(entro==0)
		printf("Imposible alocar ese proceso");
}


void recorrer(){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int suma=0;
	printf("\n--- Recorrido de la memoria --- \n*Particiones:\n*Memoria:%p\n",memoria);
	while(aux!=NULL){
		printf("\nParticion: %i :\n*Estado (Ocupado=0, Libre=1): %i\n*Tamaño:%i KB\n*Proceso: %i\n",aux->ID,aux->estado,aux->size,aux->pro);
		if(aux->estado==LIBRE)
			suma=suma+(aux->size);
		aux=(aux->siguiente);
	};
	printf("\n*Fracmentacion externa:%i KB\n\n",suma);
}

void liberar(int id){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int encontre=0;
	int proceso;
	printf("---------- ESTOY POR BORRAR, MI DIRECCION DE MEMORIA ES:-----------------------\n",memoria);
	while((encontre==0)&&(aux!=NULL)){
		proceso=(aux->pro);
		printf("Id del proceso recorrido:%i \n",proceso);
		if(proceso==id){
			encontre=1;
			aux->estado=LIBRE;
			aux->pro=-1;
			printf("--- Se elimino exitosamente el Proceso: %i ---\n",id);
		}
		else 
			aux=(aux->siguiente);
	}
	if(encontre==0)
		printf("--- No existe el Proceso: %i ---\n",id);
}
