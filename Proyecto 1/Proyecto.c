#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

int main( void ){
    char args[ MAX_LINE ]; /* command line arguments */
    int run = 1; /* flag to determine when to exit program */
    while( run ){
        int pid, i;
        char del[ MAX_LINE ] = " ";
        char argsTemp[ 20 ][ MAX_LINE ];
        char * ptr;
        printf( "osh > " );
        fflush( stdin );
        fflush( stdout ); //Vaciar Buffer
        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) parent will invoke wait() unless command included &
        */
        pid = fork();
        fgets( args, MAX_LINE, stdin );
        ptr = strtok( args, del );
        i = 0;
        while( ptr != NULL ){
            strcpy( argsTemp[ i++ ], ptr );
            ptr = strtok( NULL, del );
        }
        if( args[ strlen(args) - 1 ] == '\n' ){
            args[ strlen(args) - 1 ] = '\0';
        }
        if( strcmp( args, "exit" ) == 0 ){
            run = 0;
        }
        else{
            if( pid < 0 ){
                printf( "ERROR" );
                run = 0;
            }
            else if( pid == 0 ){ //Hijo
                //execvp( argsTemp[0],  )
            }
            else if( pid == 1 ){ //Padre
                //wait( NULL );
                printf("Child complete\n");
            }
        }
        printf( "\n" );
    }
    return 0;
}