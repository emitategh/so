
#include <windows.h>
#include <stdio.h>

HANDLE scocinero,scocina,sfuente,scomensal,scomer;

WORD WINAPI cocineroA(){
 

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
WORD WINAPI  comensalA(){
	while(1){

		WaitForSingleObject( 
            scomensal,   // handle to semaphore
            0L);           // zero-second time-out interval
		
		WaitForSingleObject( 
            scomer,   // handle to semaphore
            0L);           // zero-second time-out interval

		DWORD dwWaitResult=WaitForSingleObject( 
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

int main(){
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

    // Create worker threads
	 DWORD ThreadID;
	 DWORD ThreadID2;
	 DWORD ThreadID3;
	 DWORD ThreadID4;
	 DWORD ThreadID5;
	HANDLE aThread[2];
	
	aThread[0]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) cocineroA, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &ThreadID); // receive thread identifier
	aThread[1]=CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) comensalA, 
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &ThreadID2); // receive thread identifier
		
    

    // Wait for all threads to terminate

    WaitForMultipleObjects(2, aThread, TRUE, INFINITE);

    // Close thread and semaphore handles

    for( int i=0; i < 2; i++ )
        CloseHandle(aThread[i]);

    //CloseHandle(ghSemaphore);
	
	return 0;
}