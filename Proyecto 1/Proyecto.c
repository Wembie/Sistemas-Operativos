/*-> Juan Esteban Acosta López - Maria del Mar Villaquiran Davila <-*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_LINE 80 /* The maximum length command */

#define READ_PIPE 0 //Pipe para escritura
#define WRITE_PIPE 1 // Pipe para lectura

void execEntrada( char ** entradaArgs ){
    pid_t pid = fork();
    if( pid < 0 ){
        printf( "ERROR" );
        return;
    }
    else if( pid == 0 ){ //Hijo
        execvp( entradaArgs[ 0 ], entradaArgs );
        exit( 0 );
    }
    else if( pid == 1 ){ //Padre
        wait( NULL );
        return;
    }
}

void execEntradaPipe( char ** entrada, char ** entradaPipe ){
    //El padre crea el pipe, entonces se abre los extremos de escritura y lectura y los hijos lo heredan

    int pipefd[ 2 ]; //Extremo de lectura y escritura
    pid_t pid;
    if( pipe( pipefd ) >= 0 ){ //Verifica que el pipe se puede iniciar
        pid = fork();//Primer hijo
        if( pid >= 0 ){ //Verifica si puede hacer fork
            if( pid == 0 ){ //Hijo
                close( pipefd[ READ_PIPE ] ); //Se cierran los extremos no necesarios del pipe, entonces como primero el hijo1 va a escribir, se cierra el de lectura
                dup2( pipefd[ WRITE_PIPE ], STDOUT_FILENO ); //Para escribir por predeterminado en el file (STDOUT), este escribiendo en el extremo de escritura del pipe
                close( pipefd[ WRITE_PIPE ] ); //Se cierra 
                execvp( entrada[ 0 ], entrada );
                exit( 0 );
            }
            else{ //Padre
                
                pid = fork(); //Segundo hijo
                if( pid >= 0 ){ //Verifica si puede hacer fork
                    if( pid == 0 ){//Hijo
                        close( pipefd[ WRITE_PIPE ] ); //Se cierra el extremo de escritura
                        dup2( pipefd[ READ_PIPE ], STDIN_FILENO ); //Por defecto toma STDIN, entonces va a leer el extremo de lectura del pipe
                        close( pipefd[ READ_PIPE ] ); //Cierra 
                        execvp( entradaPipe[ 0 ], entradaPipe );
                        exit( 0 );
                    }
                    else{
                        wait( NULL );
                        wait( NULL );
                    }
                }
            }
        }
    }
}

bool tienePipe( char * entrada, char ** divisionPipe ){
    int i = 0;
    for( i = 0; i < 2; i++ ){
        divisionPipe[ i ] = strsep( &entrada, "|" ); //Tomado de https://www.delftstack.com/es/howto/c/strsep-in-c/
        if( divisionPipe[ i ] == NULL ){
            break;
        }
    }
    if( divisionPipe[ 1 ] == NULL ){
        return false;
    } 
    else{
        return true;
    }
}

void dividirLinea( char * entrada, char ** entradaArgs ){
    int i = 0;
    for( i = 0; i < MAX_LINE; i++ ){
        entradaArgs[ i ] = strsep( &entrada, " " ); //Tomado de https://www.delftstack.com/es/howto/c/strsep-in-c/
        if( entradaArgs[ i ] == NULL ){
            break;
        }
        if( strlen( entradaArgs[ i ] ) == 0 ){// ELimina el espacio de mas que se hace
            i--;
        }
    }
}

int main( void ){
    char entrada[ MAX_LINE ]; /* command line arguments */
    char * entradaArgs[ MAX_LINE ];
    char * entradaPipe[ MAX_LINE ];
    char historia[ 80 ] ;
    char directorio[ MAX_LINE * sizeof( int ) ];
    int run = 1; /* flag to determine when to exit program */
    while( run ){
        char * ptr;
        getcwd( directorio, sizeof( directorio ) ); //Toma el Directorio -> TOMADO DE https://www.delftstack.com/es/howto/c/get-current-directory-in-c/
        printf( "Directorio: %s\nosh > ", directorio );
        fflush( stdin );
        fflush( stdout ); //Vaciar Buffer
        fgets( entrada, MAX_LINE, stdin ); //TakeInput
        if( entrada[ 0 ] != '\n' ){ //Enter
            entrada[ strcspn( entrada, "\n" ) ] = 0; //buscará en la cadena name el primer match con \n y devolverá la posición en name en la cual fue encontrado el match. // TOMADO de https://www.tutorialspoint.com/c_standard_library/c_function_strcspn.htm
            if( strcmp( entrada, "exit" ) == 0 ){
                exit( 0 );
            }
            else{
                bool contienePipe, bandera = false;
                char * divisionPipe[ 2 ];
                char * p = historia;
                if( strcmp( entrada, "!!" ) == 0 ){
                    if( *p == '@' ){//No se, pero sirve, es lo importante. AMEN DIOS PATRIA. @��u7VC EJEMPLO
                        printf( "No hay comandos en la historia\n" );
                        continue;
                    }
                    else{ // !! con comando
                        strcpy( entrada, historia ); 
                        bandera = true;
                    }
                }
                if( !bandera ){
                    strcpy( historia, entrada );
                }
                contienePipe = tienePipe( entrada, divisionPipe );
                if( contienePipe ){
                    dividirLinea( divisionPipe[ 0 ], entradaArgs );
                    dividirLinea( divisionPipe[ 1 ], entradaPipe );
                    execEntradaPipe( entradaArgs, entradaPipe );
                }
                else{
                    dividirLinea( entrada, entradaArgs );
                    if( strcmp( entradaArgs[ 0 ], "cd" ) == 0 ){
                        chdir( entradaArgs[ 1 ] ); //Tomado de https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
                    } 
                    else{ 
                        execEntrada( entradaArgs );  
                    } 
                }
            }
        }
        else{
            continue;
        }
        usleep( 100000 ); //Con eso se mejora la estetica pero es un poquito lento. pork? no sabemos PERO DIOOOOOOOOOOOOOOOOOOOOOOO Y QUEDO BONITO :3, osea por que usleep y no sleep? por que es que us significa nosotros entonces como lo hicimos nosotros pues aja, entonces marimar y juanes = nosotros por ende usleep gano la apuesta, gracias, bendiciones
    }
    return 0;
}