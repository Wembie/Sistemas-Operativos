#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include <pthread.h> 
#include <stdlib.h>

typedef struct __myarg_t {
	char * name;
	char petition;
} myarg_t;

void *worker(void *arg){
	myarg_t *m = (myarg_t *) arg;
    char Lista[1000];

	pid_t pid = fork();
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    char *line = NULL;
    size_t  len = 0;
    ssize_t read;
    FILE * datos = fopen( "nombresContenedores.txt", "at" );
    
    if(datos == NULL){
        perror("ERROR EN ABRIR EL ARCHIVO");
    }
    while ((read = getline(&line, &len, datos)) != -1) {
        line[strcspn(line, "\n")] = 0;
        if (!strcmp(line, m->name)) {
            printf("SI");
            break;
        }
    }
    printf("Holita");

    //fputs(&m->name, datos);
	if(pid == 0){
		if(strcmp(&m->petition, "1") == 0){
			execlp("docker", "docker", "run", "-di", "--name", m->name, "ubuntu:latest", "/bin/bash", NULL);
		} else if(strcmp(&m->petition, "3") == 0){
			execlp("docker", "docker", "stop", &m->name, NULL);
		} else if(strcmp(&m->petition, "4") == 0){
			execlp("docker", "docker", "rm", &m->name, NULL);
		} else if(strcmp(&m->petition, "2") == 0){
			execlp("docker", "docker", "ps", NULL);
		}
	} 
	else{
		if(strcmp(&m->petition, "1") == 0){
			printf("Container creado: ");
		} else if(strcmp(&m->petition, "3") == 0){
			printf("Container parado: ");
		} else if(strcmp(&m->petition, "4") == 0){
			printf("Container borrado: ");
		} else if(strcmp(&m->petition, "2") == 0){
			printf("Listed");
		}

	}
    pthread_mutex_unlock( &mutex );
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
						//targ[cantidadHilos].name = *client_message;
                        strcpy( targ[cantidadHilos].name, client_message);
						targ[cantidadHilos].petition = '1';
						pthread_create(&tid[cantidadHilos], &attr, worker, &targ[cantidadHilos]); 	
					}	
                    printf("NOMBRE: %s \n", targ[cantidadHilos].name);
                    
                    
				}
				else if( strcmp( client_message, "2" ) == 0 ){
					//Listar
					char server_message[] = "Listando... (Dar Enter)";
					memset(client_message, 0, 2000);
					send(client_sock, server_message, strlen(server_message), 0);
					if(recv(client_sock, client_message, 2000, 0) > 0) {
						printf("received message: %s\n", client_message);
						//targ[cantidadHilos].name = *client_message;
                        strcpy( targ[cantidadHilos].name, client_message);
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
						//targ[cantidadHilos].name = *client_message;
                        strcpy( targ[cantidadHilos].name, client_message);
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
						//targ[cantidadHilos].name = *client_message;
                        strcpy( targ[cantidadHilos].name, client_message);
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