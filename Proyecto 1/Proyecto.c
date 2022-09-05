#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

void ejecutarPipe( char ** argsTemp, int pipe, int * run ){
    if( pipe == 0 ){ //No tiene Pipe
        argsTemp[ 2 ] = NULL;
        int pid = fork();
        if( pid < 0 ){
            printf( "ERROR" );
            *run = 0;
        }
        else if( pid == 0 ){ //Hijo
            execvp( argsTemp[ 0 ], argsTemp );
            exit( 0 );
        }
        else if( pid == 1 ){ //Padre
            wait( NULL );
        }
    }
    else{ //Tiene Pipe
        //To do
    }
} 

int dividirLinea( char * args, char ** argsTemp ){
    int i = 0, indicePipe = 0;
    char * ptr = strtok( args, " " );
    while( ptr != NULL ){
        argsTemp[ i++ ] = ptr ;
        if( strcmp( ptr, "|" ) == 0 ){
            indicePipe = i - 1;
        }
        ptr = strtok( NULL, " " );
    }
    if( args[ strlen( args ) - 1 ] == '\n' ){
        args[ strlen( args ) - 1 ] = '\0';
    }
    //Falta quitar el \n en el argstemp
    return indicePipe;
}

int main( void ){
    char args[ MAX_LINE ]; /* command line arguments */
    char historia[  ] = "No commands in history.";
    int run = 1; /* flag to determine when to exit program */

    while( run ){
        int pid, tienePipe;
        char * argsTemp[ MAX_LINE ];
        char * ptr;
        printf( "osh > " );
        fflush( stdout ); //Vaciar Buffer
        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) parent will invoke wait() unless command included &
        */
        //pid = fork();
        fgets( args, MAX_LINE, stdin );
        tienePipe = dividirLinea( args, argsTemp );
        if( strcmp( args, "exit" ) == 0 ){
            run = 0;
        }
        else{
            ejecutarPipe( argsTemp, tienePipe, &run );
        }
        printf( "\n" );
    }
    return 0;
}