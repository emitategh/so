
#include <windows.h>
#include <stdio.h>



HANDLE scocinero,scocina,sfuente,scomensal,scomer;

void* cocineroA(){
	while(1){
		
		WaitForSingleObject( 
            scocinero,   // handle to semaphore
            0L);           // zero-second time-out interval
		WaitForSingleObject( 
            scocina,   // handle to semaphore
            0L);           // zero-second time-out interval
		for(int j=0;j<100;j++){
			ReleaseSemaphore(sfuente,
				1,		// cantidad que se aumenta
				NULL);
			printf("Cocinando: A\n");
		};
		ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
		ReleaseSemaphore(scomer,
			1,			// cantidad que se aumenta
			NULL);
	};
}

void* cocineroB(){
	while(1){
		
		WaitForSingleObject( 
            scocinero,   // handle to semaphore
            0L);           // zero-second time-out interval
		WaitForSingleObject( 
            scocina,   // handle to semaphore
            0L);           // zero-second time-out interval
		for(int j=0;j<100;j++){
			ReleaseSemaphore(sfuente,
				1,		// cantidad que se aumenta
				NULL);
			printf("Cocinando: B\n");
		};
		ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
		ReleaseSemaphore(scomer,
			1,			// cantidad que se aumenta
			NULL);
	};
}

void* comensalA(){

	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Juan: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Juan: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Juan despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void* comensalB(){
	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Roberto: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Roberto: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Roberto despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void* comensalC(){
	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Gaston: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Gaston: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Gaston despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void* comensalD(){
	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Cecilia: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Cecilia: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Cecilia despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void* comensalE(){
	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Wilson: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Wilson: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Wilson despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void* comensalF(){
	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Cristian: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Cristian: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Cristian despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void* comensalG(){
	while(1){

		DWORD dwWaitComensal = WaitForSingleObject( 
            scomensal,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
		
		DWORD dwWaitComer = WaitForSingleObject( 
            scomer,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

		DWORD dwWaitFuente =WaitForSingleObject( 
            sfuente,   // handle to semaphore
            0L);           // zero-second time-out interval

		switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
            printf("Motorola: Me estoy sirviendo\n");
            ReleaseSemaphore(scomensal,
			1,			// cantidad que se aumenta
			NULL);
			ReleaseSemaphore(sfuente,
			1,			// cantidad que se aumenta
			NULL);
			for(int j=0;j<92013;j++){

			};
			printf("Motorola: Comiendo\n");

            break;

            case WAIT_TIMEOUT: 
                printf("Motorola despierta a los cocineros\n");
                
				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocinero,
					1,			// cantidad que se aumenta
					NULL);

				ReleaseSemaphore(scocina,
					1,			// cantidad que se aumenta
					NULL);
                break; 
		};
	};
}
void main(){
	DWORD h1,h2,h3,h4,h5,h6,h7,h8,h9;
	
	scocinero = CreateSemaphore( 
        NULL,           // default security attributes
        1,  // initial count
        100,  // maximum count
        NULL);          // unnamed semaphore
	scocina	= CreateSemaphore( 
        NULL,           // default security attributes
        1,  // initial count
        100,  // maximum count
        NULL);  
	scomensal= CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        100,  // maximum count
        NULL);  
	scomer = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        100,  // maximum count
        NULL);  
	sfuente	 = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        100,  // maximum count
        NULL);  
	
	HANDLE aThread[9];


	aThread[0]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) cocineroA, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h1); // receive thread identifier
	aThread[1]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) cocineroB, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h2); // receive thread identifier
	aThread[2]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalA, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h3); // receive thread identifier

	aThread[3]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalB, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h4); // receive thread identifier
	aThread[4]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalC, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h5); // receive thread identifier
	aThread[5]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalD, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h6); // receive thread identifier
	aThread[6]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalE, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h7); // receive thread identifier
	aThread[7]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalF, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h8); // receive thread identifier
	aThread[8]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalG, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &h9); // receive thread identifier
	
	// Wait for all threads to terminate

    WaitForMultipleObjects(9, aThread, TRUE, INFINITE);

    // Close thread and semaphore handles

    for( int i=0; i < 9; i++ )
        CloseHandle(aThread[i]);

    //CloseHandle(ghSemaphore);
	
	return 0;
}
}
