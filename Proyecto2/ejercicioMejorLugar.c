#include <stdio.h>
#include <stdlib.h>

struct celda{
	int estado;
	int size;
	int ID;
	char pro;
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
	memoria->pro='*';
	cant=1;
	printf("MEMORIA DE :%i KB\n",memoria->size);
	insertar('A',15360);
	insertar('D',15360);
	insertar('C',15360);
	recorrer();
	liberar('D');
	insertar('X',8192);
	recorrer();
};

void insertar(char id,int tam_pro){
	printf("Estoy por insertar el Proceso: %c DE :%i KB\n",id,tam_pro);
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	struct celda* candidato=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int tam_particion;
	int menor=65536; // ES EL MENOR TAMAÑO

	//BUSCO EL MEJOR CANDIDATO
	while(aux!=NULL){
		tam_particion=aux->size;
		if((aux->estado=LIBRE)&&(tam_particion>=tam_pro)&&(tam_particion<=menor)){
			candidato=aux;
			menor=tam_particion;
		}
		aux=(aux->siguiente);
	};
	if(menor>=tam_pro){
		printf("--- Se aloco exitosamente el proceso: %c ---\n",id);
		struct celda* nueva=(struct celda *)malloc(sizeof(struct celda));
		nueva->ID=cant;
		nueva->estado=OCUPADO;
		nueva->siguiente=candidato;
		nueva->size=tam_pro;
		nueva->anterior=(candidato->anterior);
		nueva->pro=id;
		if((candidato->anterior)!=NULL){
			(candidato->anterior)->siguiente=nueva;
			 //MEDIO CHANCHO, ESTO ES EN CASO DE SER EL PRIMER PROCESO EN USAR LA MEMORIA SE MODIFIQUE EL PUNTERO
		}
		else{
			printf("CAMBIE EL PUNTERO\n");
			memoria=nueva;
		}

		candidato->size=tam_particion-tam_pro;
		candidato->anterior=nueva;
		cant++;
	}
	else
		printf("Imposible alocar ese proceso");
}


void recorrer(){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int suma=0;
	printf("\n--- Recorrido de la memoria --- \n*Particiones:\n*Memoria:%p\n",memoria);
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
