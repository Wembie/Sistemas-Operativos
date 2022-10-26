#include <stdio.h>
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <pthread.h> 
#include <stdlib.h>
#include <sys/wait.h>

typedef struct __myarg_t {
	char name[100];
	char petition;
} myarg_t;

int buscarNombre(char name[100]){
	FILE * datos = fopen( "nombresContenedores.txt", "r" );
	if(datos == NULL){
        perror("ERROR EN ABRIR EL ARCHIVO");
		exit(1);
    }
	char *linea;
	int ans = 0;
	while(fgets(linea, 100, datos) && ans == 0){
    	linea = strtok(linea, " ");
		if(strcmp(name, linea) == 0){
			ans = 1;
		}
	}
	fclose(datos);
	return ans;
}

char *obtenerEstado(char name[100]){
	FILE * datos = fopen( "nombresContenedores.txt", "r" );
	if(datos == NULL){
        perror("ERROR EN ABRIR EL ARCHIVO");
		exit(1);
    }
	char *linea;
	int ans = 0;
	while(fgets(linea, 100, datos) && ans == 0){
    	linea = strtok(linea, " ");
		if(strcmp(name, linea) == 0){
			ans = 1;
			linea = strtok(NULL, "\n");
		}
	}
	fclose(datos);
	if(ans == 0)
	{
		return NULL;
	}
	return linea;
}

void modificarEstado(char name[100]){
	FILE * datos = fopen("nombresContenedores.txt", "r");
	FILE * nuevo = fopen("temp.txt", "w");
	if(datos == NULL){
        perror("ERROR EN ABRIR EL ARCHIVO");
		exit(1);
    }
	char *linea, *nombreTemp;
	while(fgets(linea, 100, datos)){
    	nombreTemp = strtok(linea, " ");
		if(strcmp(name, nombreTemp) == 0){
			fputs(nombreTemp, nuevo);
			fputs(" detenido\n", nuevo);
		}
		else{
			fputs(linea, nuevo);
		}
	}
	fclose(datos);
	fclose(nuevo);
	datos = fopen("nombresContenedores.txt", "w");
	nuevo = fopen("temp.txt", "r");
	while(fgets(linea, 100, nuevo)){
		fputs(linea, datos);
	}
	fclose(datos);
	fclose(nuevo);
}

void borrarContenedor(char name[100]){
	FILE * datos = fopen("nombresContenedores.txt", "r");
	FILE * nuevo = fopen("temp.txt", "w");
	if(datos == NULL){
        perror("ERROR EN ABRIR EL ARCHIVO");
		exit(1);
    }
	char *linea, *nombreTemp;
	while(fgets(linea, 100, datos)){
    	nombreTemp = strtok(linea, " ");
		if(strcmp(name, nombreTemp) != 0){
			fputs(linea, nuevo);
		}
	}
	fclose(datos);
	fclose(nuevo);
	datos = fopen("nombresContenedores.txt", "w");
	nuevo = fopen("temp.txt", "r");
	while(fgets(linea, 100, nuevo)){
		fputs(linea, datos);
	}
	fclose(datos);
	fclose(nuevo);
}

void escribirEnArchivo(char name[100]){
	FILE * datos = fopen( "nombresContenedores.txt", "at" );
	fputs(name, datos);
	fputs(" activo\n", datos);
	fclose(datos);
}

void mostrarContenedores(){
	FILE * datos = fopen("nombresContenedores.txt", "r");
	if(datos == NULL){
        perror("ERROR EN ABRIR EL ARCHIVO");
		exit(1);
    }
	char *linea;
	while(fgets(linea, 100, datos)){
    	printf("%s", linea);
	}
	fclose(datos);
}

void *worker(void *arg){
	myarg_t *m = (myarg_t *) arg;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    char *line = NULL;
    size_t  len = 0;
    ssize_t read;
	pid_t pid = fork();
	if(pid == 0){
		if(m->petition == '1'){
			if(buscarNombre(m->name) == 0){
				pthread_mutex_lock(&mutex);
				escribirEnArchivo(m->name);
				execlp("docker", "docker", "run", "-di", "--name", &m->name, "ubuntu:latest", NULL, NULL);
				pthread_mutex_unlock( &mutex );
			}
		} else if(m->petition == '3'){
			pthread_mutex_lock(&mutex);
			if(!strcmp(obtenerEstado(m->name), "activo")){ 
				modificarEstado(m->name);
				execlp("docker", "docker", "stop", &m->name, NULL); 
				pthread_mutex_unlock( &mutex );
			}
		} else if(m->petition == '4'){
			pthread_mutex_lock(&mutex);
			if(!strcmp(obtenerEstado(m->name), "detenido")){
				borrarContenedor(m->name);
				execlp("docker", "docker", "rm", &m->name, NULL);
				pthread_mutex_unlock( &mutex );
			}
		} else if(m->petition == '2'){
			pthread_mutex_lock(&mutex);
			mostrarContenedores();
			pthread_mutex_unlock( &mutex );
		} else if(m->petition == '5'){
			printf("UwU\n");
		}
		
	} 
	else{
		wait(NULL);
		if(m->petition == '1'){
			printf("Container created: ");
		} else if(m->petition == '3'){
			printf("Container stopped: ");
		} else if(m->petition == '4'){
			printf("Container deleted: ");
		} else if(m->petition == '2'){
			printf("Listed");
		}
	}
}

int main(int argc , char *argv[]) {
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;  // https://github.com/torvalds/linux/blob/master/tools/include/uapi/linux/in.h
	char client_message[2000];
	
	// Create socket
    // AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol) 
    // SOCK_STREAM: TCP(reliable, connection oriented)
    // SOCK_DGRAM: UDP(unreliable, connectionless)
    // Protocol value for Internet Protocol(IP), which is 0
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");
	
	pthread_t tid[100];
	myarg_t targ[100]; 
    /* An array with argument data for each thread. */
	//targ[ 0 ] = 0;
	int cantidadHilos = 0;
    /* Attributes (stack size, scheduling information) for the threads. */
    pthread_attr_t attr;
    /* Get default attributes for the threads. */
    pthread_attr_init(&attr);
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);
	
	//Bind the socket to the address and port number specified
	if( bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	// Listen
    // It puts the server socket in a passive mode, where it waits for the client 
    // to approach the server to make a connection. The backlog, defines the maximum 
    // length to which the queue of pending connections for sockfd may grow. If a connection 
    // request arrives when the queue is full, the client may receive an error with an 
    // indication of ECONNREFUSED.
	// https://man7.org/linux/man-pages/man2/listen.2.html
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);


	while(1) {
		//accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if(client_sock < 0) {
			perror("accept failed");
			return 1;
		}
		puts("Connection accepted");


		while(1){			
			memset(client_message, 0, 2000);
			//Receive a message from client
			if(recv(client_sock, client_message, 2000, 0) > 0) {
				printf("received message: %s\n", client_message);
				//Send the message back to client
                char server_message[] = " ";
				if( strcmp( client_message, "1" ) == 0 ){
					char server_message[] = "Por favor digita el nombre de la imagen a crear: ";
					memset(client_message, 0, 2000);
					send(client_sock, server_message, strlen(server_message), 0);
					if(recv(client_sock, client_message, 2000, 0) > 0) {
						printf("received message: %s\n", client_message);
						strcpy(targ[cantidadHilos].name, client_message);
						targ[cantidadHilos].petition = '1';
						pthread_create(&tid[cantidadHilos], &attr, worker, &targ[cantidadHilos]); 	
					}	
				}
				else if( strcmp( client_message, "2" ) == 0 ){
					//Listar
					char server_message[] = "Listando... ";
					memset(client_message, 0, 2000);
					send(client_sock, server_message, strlen(server_message), 0);
					if(recv(client_sock, client_message, 2000, 0) > 0) {
						printf("received message: %s\n", client_message);
						strcpy(targ[cantidadHilos].name, client_message);
						targ[cantidadHilos].petition = '2';
						pthread_create(&tid[cantidadHilos], &attr, worker, &targ[cantidadHilos]); 
					}
						
				}
				else if( strcmp( client_message, "3" ) == 0 ){
					//Detener
					char server_message[] = "Por favor digita el nombre de la imagen a detener: ";
					memset(client_message, 0, 2000);
					send(client_sock, server_message, strlen(server_message), 0);
					if(recv(client_sock, client_message, 2000, 0) > 0) {
						printf("received message: %s\n", client_message);
						strcpy(targ[cantidadHilos].name, client_message);
						targ[cantidadHilos].petition = '3';
						pthread_create(&tid[cantidadHilos], &attr, worker, &targ[cantidadHilos]); 	
					}
				}
				else if( strcmp( client_message, "4" ) == 0 ){
					//Borrar
					memset(client_message, 0, 2000);
					send(client_sock, server_message, strlen(server_message), 0);
					if(recv(client_sock, client_message, 2000, 0) > 0) {
						printf("received message: %s\n", client_message);
						strcpy(targ[cantidadHilos].name, client_message);
						targ[cantidadHilos].petition = '4';
						pthread_create(&tid[cantidadHilos], &attr, worker, &targ[cantidadHilos]); 
					}
				}
				else{
					char server_message[] = "ERROR";
				}
				cantidadHilos++;
			}
			
		}
	}
	return 0;
}
