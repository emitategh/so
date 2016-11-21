#include <stdio.h>
#include <stdlib.h>

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

void insertar(int id,int tam_pro);
void recorrer();
void liberar(int id);
void compactar();
int rand_range(int min_n, int max_n);
void darRequerimientos(int n);

int cant_process;//CANTIDAD DE PROCEESOS
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
	int* procesos=malloc(sizeof(int*)*5);
	cant_process=0;
	recorrer();
	darRequerimientos(10);
	recorrer();
};

void insertar(int id,int tam_pro){
	printf("\n *************** Insertar el Proceso: %i DE :%i KB *************** \n",id,tam_pro);
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
				//printf("CAMBIE EL PUNTERO\n");
				memoria=nueva;
			}

			aux->size=tam_particion-tam_pro;
			aux->anterior=nueva;
			entro=1;
			cant++;
			cant_process++;
			printf(" 	--- El proceso fue alocado exitosamente ---\n");
		}
		else 
			aux=(aux->siguiente);
	}
	if(entro==0)
		printf(" 	---Imposible alocar ese proceso ---\n");
}


void recorrer(){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int suma=0;
	printf("\n *************** Recorrido de la memoria *************** \n*Particiones:\n*Memoria:%p \n",memoria);
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
	printf("\n *************** ELIMANDO EL PROCESO:%i *************** \n",id);
	while((encontre==0)&&(aux!=NULL)){
		proceso=(aux->pro);
		//printf("Id del proceso recorrido:%i \n",proceso);
		if(proceso==id){
			encontre=1;
			aux->estado=LIBRE;
			aux->pro=-1;
			printf("	  --- Se elimino exitosamente el Proceso: %i ---\n",id);
			compactar();
			//compactar();
		}
		else 
			aux=(aux->siguiente);
	}
	if(encontre==0)
		printf("		  --- No existe el Proceso: %i ---\n",id);
}

void compactar(){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	struct celda* ant=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int proceso;
	while(aux!=NULL){
		ant=aux->anterior;
		if(ant!=NULL){
			if((aux->estado==LIBRE)&&(ant->estado==LIBRE)){
				//TENGO QUE COMPACTAR DOS UNIDADES LIBRES
				int size=ant->size;
				ant->size=size+aux->size;
				struct celda* sig=(struct celda *)malloc(sizeof(struct celda));
				sig=aux->siguiente;
				if(sig==NULL){
					ant->siguiente=NULL;
					free(aux);
				}
				else{

					ant->siguiente=sig;
					(sig->anterior)=ant;
					free(aux);
				};	
			aux=ant;
			}
			else{
				aux=aux->siguiente;
			}
		}
		else{
			aux=aux->siguiente;
		}
	};
};


int rand_range(int min_n, int max_n){
    return rand() % (max_n - min_n + 1) + min_n;
}


void darRequerimientos(int n){
	int cont=0;
	int i=0;
	time_t t;
   	int size;
   	int r;
   //	srand((unsigned) time(&t));
	printf("\n ----------------------- DAR REQUERIMIENTOS ----------------------- \n");
	while(i!=n){
		r= rand() % 2;
		if(r==0){
			//ELIJO UN PROCESO AL AZAR PARA LIBERAR
			int victima=rand()%cant_process;
			liberar(victima);
		}
		else{
			//CREO NUEVOS REQUERIMIENTOS
			size=rand_range(100,16348);
			insertar(cant_process,size);
		}
		i++;
	};
};