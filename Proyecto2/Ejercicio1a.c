#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Secuencia AB(C o D)E...

int main(){
	int i;
	int A[2], B[2], C[2], D[2], E[2];
	char buffer[1];
	
	pipe(A);
	pipe(B);
	pipe(C);
	pipe(D);
	pipe(E);
	buffer[0]='W';
	write(A[1], buffer, 1);
	
	pid_t pid1=fork();
	if(pid1==0){
		//PROCESO A

		//CIERRO PARA LECCTURA
		close(B[0]);
		close(C[0]);
		close(D[0]);
		close(E[0]);

		//CIERRO PARA ESCRITURA
		close(A[1]);
		close(C[1]);
		close(D[1]);
		close(E[1]);
		
		while(1){

			read(A[0], buffer, 1);

			sleep(2);
			printf("A - ");
			fflush(stdout);
			buffer[0]='W';
			write(B[1], buffer, 1);
		};
	}
	pid_t pid2=fork();
	if(pid2==0){
		//PROCESO B

		//CIERRO PARA LECTURA
		close(A[0]);
		close(C[0]);
		close(D[0]);
		close(E[0]);

		//CIERRO PARA ESCRITURA
		close(A[1]);
		close(B[1]);
		close(D[1]);
		close(E[1]);

		while(1){

			read(B[0],buffer,1);
			sleep(2);
			printf("B - ");
			fflush(stdout); //NI IDEA
			buffer[0]='W';
			write(C[1], buffer, 1);

		};
	};
	pid_t pid3=fork();
	if(pid3==0){
		//PROCESO C

		//CIERRO PARA LECTURA
		close(A[0]);
		close(B[0]);
		close(D[0]);
		close(E[0]);

		//CIERRO PARA ESCRITURA
		close(A[1]);
		close(B[1]);
		close(C[1]);
		close(E[1]);

		while(1){
			read(C[0],buffer,1);
			sleep(2);
			printf("C - ");
			fflush(stdout); //NI IDEA
			buffer[0]='W';
			write(D[1], buffer, 1);
		}
	};
	pid_t pid4=fork();
	if(pid4==0){
		//PROCESO D

		//CIERRO PARA LECTURA
		close(A[0]);
		close(B[0]);
		close(C[0]);
		close(E[0]);

		//CIERRO PARA ESCRITURA
		close(A[1]);
		close(B[1]);
		close(C[1]);
		close(D[1]);

		while(1){
			read(D[0],buffer,1);
			sleep(2);
			printf("D - ");
			fflush(stdout); //NI IDEA
			buffer[0]='W';
			write(E[1], buffer, 1);
		}
	};
	pid_t pid5=fork();
	if(pid5==0){
		//PROCESO E

		//CIERRO PARA LECTURA
		close(A[0]);
		close(B[0]);
		close(C[0]);
		close(D[0]);

		//CIERRO PARA ESCRITURA
		close(B[1]);
		close(C[1]);
		close(D[1]);
		close(E[1]);

		while(1){
			read(E[0],buffer,1);
			sleep(2);
			printf("E.\n");
			fflush(stdout); //NI IDEA
			buffer[0]='W';
			write(A[1], buffer, 1);
		}
	};

	for(i=0;i<5;i++)
		wait(NULL);
		
	return 0;
};