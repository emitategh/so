#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int A[2];
	int B[2];
	int CD[2];
	int E[2];
	int F[2];

	//CREO LOS PIPES 
	pipe(A);
	pipe(B);
	pipe(CD);
	pipe(E);
	pipe(F);

	//CREO EL BUFFER
	char buff[1];
	buff[0]='a';

	//INCIALIZO EL PRIMER PIPE
	write(A[1],buff,1);

	pid_t pA=fork();
	if(pA==0){
		//PROCESO A

		//CIERRO PARA LECTURA LOS PIPES
		close(B[0]);
		close(CD[0]);
		close(E[0]);
		close(F[0]);

		//CIERRO PARA ESCRITURA LOS PIPES
		close(A[1]);
		close(CD[1]);
		close(E[1]);
		close(F[1]);

		while(1){

			read(A[0],buff,1);
			
			printf("A - ");
			fflush(stdout);
			buff[0]='9';
			write(B[1],buff,1);
		};
	};

	pid_t pB=fork();
	if(pB==0){
		//PROCESO B

		//CIERRO PARA LECTURA LOS PIPES
		close(A[0]);
		close(CD[0]);
		close(E[0]);
		close(F[0]);

		//CIERRO PARA ESCRITURA LOS PIPES
		close(A[1]);
		close(B[1]);
		close(E[1]);
		close(F[1]);

		while(1){

			read(B[0],buff,1);
			
			printf("B - ");
			fflush(stdout);
			buff[0]='9';
			write(CD[1],buff,1);
		};
	};

	pid_t pC=fork();
	if(pC==0){
		//PROCESO C

		//CIERRO PARA LECTURA LOS PIPES
		close(A[0]);
		close(B[0]);
		close(E[0]);
		close(F[0]);
		//CIERRO PARA ESCRITURA LOS PIPES
		close(A[1]);
		close(B[1]);
		close(CD[1]);
		close(F[1]);

		while(1){

			read(CD[0],buff,1);
			
			printf("C - ");
			fflush(stdout);
			buff[0]='9';
			write(E[1],buff,1);
		};
	};

	pid_t pD=fork();
	if(pD==0){
		//PROCESO D

		//CIERRO PARA LECTURA LOS PIPES
		close(A[0]);
		close(B[0]);
		close(E[0]);
		close(F[0]);

		//CIERRO PARA ESCRITURA LOS PIPES
		close(A[1]);
		close(B[1]);
		close(CD[1]);
		close(F[1]);

		while(1){

			read(CD[0],buff,1);
			
			printf("D - ");
			fflush(stdout);
			buff[0]='9';
			write(E[1],buff,1);
		};
	};

	pid_t pE=fork();
	if(pE==0){
		//PROCESO E

		//CIERRO PARA LECTURA LOS PIPES
		close(A[0]);
		close(B[0]);
		close(CD[0]);
		close(F[0]);

		//CIERRO PARA ESCRITURA LOS PIPES
		close(B[1]);
		close(CD[1]);
		close(E[1]);

		int e=0;
		while(1){

			read(E[0],buff,1);
			
			if(e==0){
				
				printf("E.\n");
				fflush(stdout);
				buff[0]='9';
				write(A[1],buff,1);
				e++;
			}
			else{
				
				printf("E - ");
				fflush(stdout);
				buff[0]='9'; 
				write(F[1],buff,1);
				e=0;
			};
		};
	};
	pid_t pF=fork();
	if(pF==0){
		//PROCESO F

		//CIERRO LA LECTURA
		close(A[0]);
		close(B[0]);
		close(CD[0]);
		close(E[0]);

		//CIERRO LA ESCRITURA
		close(F[1]);
		close(B[1]);
		close(CD[1]);
		close(E[1]);

		while(1){
			read(F[0],buff,1);
			
			printf("F.\n");
			fflush(stdout);
			buff[0]='s';
			write(A[1],buff,1);
		};
	};
	for(int i=0;i<6;i++){
		wait(NULL);
	};
	return 0;
};