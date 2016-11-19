#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Secuencia AB(C o D)E...

int main()
{
	int i;
	int A[2], B[2], X[2], E[2];
	char buffer[1];
	
	pipe(A);
	pipe(B);
	pipe(X);
	pipe(E);
	
	buffer[0]='W';
	write(A[1], buffer, 1);
	
	pid_t pid1=fork();
	if(pid1==0)	//PROCESO A
	{	
		close(B[0]);
		close(X[0]);
		close(E[0]);
		close(A[1]);
		close(X[1]);
		close(E[1]);
		
		while(1)
		{
			read(A[0], buffer, 1);
			printf("A");
			fflush(stdout);
			buffer[0]='W';
			write(B[1], buffer, 1);
		}
	}
	
	pid_t pid2=fork();
	if(pid2==0)	//PROCESO B
	{
		close(A[0]);
		close(X[0]);
		close(E[0]);
		close(A[1]);
		close(B[1]);
		close(E[1]);
		
		while(1)
		{
			read(B[0], buffer, 1);
			printf("B");
			fflush(stdout);
			buffer[0]='W';
			write(X[1], buffer, 1);
		}
	}
	
	pid_t pid3=fork();
	if(pid3==0)	//PROCESO C
	{
		close(A[0]);
		close(B[0]);
		close(E[0]);
		close(A[1]);
		close(X[1]);
		close(B[1]);
		
		while(1)
		{
			read(X[0], buffer, 1);
			printf ("C");
			fflush(stdout);
			buffer[0]='W';
			write(E[1], buffer, 1);
		}
	}
			
	pid_t pid4=fork();
	if(pid4==0)	//PROCESO D
	{	
		close(A[0]);
		close(B[0]);
		close(E[0]);
		close(A[1]);
		close(B[1]);
		close(X[1]);
		
		while(1)
		{
			read(X[0], buffer, 1);
			printf ("D");
			fflush(stdout);
			buffer[0]='W';
			write(E[1], buffer, 1);
		}
	}
	
	pid_t pid5=fork();
	if(pid5==0)	//PROCESO E
	{
		close(A[0]);
		close(B[0]);
		close(X[0]);
		close(B[1]);
		close(X[1]);
		close(E[1]);
		
		while(1)
		{
			read(E[0], buffer, 1);
			printf("E");
			fflush(stdout);
			buffer[0]='W';
			write(A[1], buffer, 1);
		}
	}
	
	for(i=0;i<5;i++)
		wait(NULL);
		
	return 0;
}

