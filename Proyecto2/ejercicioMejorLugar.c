#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	cant_process=0;
	printf("MEMORIA DE :%i KB\n",memoria->size);
	/*insertar(10,8192);
	insertar(11,15360);
	insertar(12,8192);
	insertar(13,8192);
	insertar(14,15360);
	recorrer();
	liberar(11);
	//recorrer();
	liberar(13);
	//recorrer();
	insertar(15,8192);
	*/
	//darRequerimientos(15);
	
	insertar(0,608);
	insertar(1,10037);
	insertar(2,9543);
	liberar(0);
	insertar(3,3484);
	liberar(3);
	insertar(4,3861);
	liberar(1);
	recorrer();
	insertar(5,2568);
	recorrer();
};

void insertar(int id,int tam_pro){
	printf("\n----------------------- Insertando el Proceso: %i DE :%i KB ----------------------- \n",id,tam_pro);
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	struct celda* candidato=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int tam_particion;
	int menor=65536; // ES EL MENOR TAMAÑO

	//BUSCO EL MEJOR CANDIDATO
	while(aux!=NULL){
		tam_particion=aux->size;
		if((aux->estado==LIBRE)&&(tam_particion>=tam_pro)&&(tam_particion<=menor)){
			candidato=aux;
			menor=tam_particion;
		}
		aux=(aux->siguiente);
	};
	if(menor>tam_pro){
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
			memoria=nueva;
		}

		(candidato->size)=menor-tam_pro;
		(candidato->anterior)=nueva;
		cant++;
		cant_process++;
		printf("		--- Se aloco exitosamente el proceso: %i en la particion:%i ---\n",id,candidato->ID);
	}
	else if(menor==tam_pro){
		candidato->pro=id;
		candidato->estado=OCUPADO;
		printf("		--- Se aloco exitosamente el proceso: %i en la particion:%i ---\n",id,candidato->ID);
	}
	else
		printf("		--- Imposible alocar ese proceso ---\n");
}	


void recorrer(){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int suma=0;
	printf("\n----------------------- Recorrido de la memoria ----------------------- \n*Particiones:\n");
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
	printf("\n----------------------- ELIMINANDO EL PROCESO:%i -----------------------\n",id);
	while((encontre==0)&&(aux!=NULL)){
		proceso=(aux->pro);
		//printf("Id del proceso recorrido:%i \n",proceso);
		if(proceso==id){
			encontre=1;
			aux->estado=LIBRE;
			aux->pro=-1;
			printf("		--- Se elimino exitosamente el Proceso: %i ---\n",id);
			compactar();
			//compactar();
		}
		else 
			aux=(aux->siguiente);
	}
	if(encontre==0)
		printf("		--- No existe el Proceso: %i ---\n",id);
};
void compactar(){
	struct celda* aux=(struct celda *)malloc(sizeof(struct celda));
	struct celda* ant=(struct celda *)malloc(sizeof(struct celda));
	aux=memoria;
	int proceso;
	printf("\n 			--- COMPACTANDO --- \n");
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
};


void darRequerimientos(int n){
	int cont=0;
	int i=0;
	time_t t;
   	int size;
   	int r;
   //	srand((unsigned) time(&t));
	printf("\n\n----------------------- DAR REQUERIMIENTOS ----------------------- \n");
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
