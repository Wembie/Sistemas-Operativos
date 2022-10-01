#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include <pthread.h> 

void *worker(void *arg){
	int id = *(int*) arg;
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
    /* An array with argument data for each thread. */
    int targ[100]; 
	targ[ 0 ] = 0;
	int cantidadHilos = 0
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
				char * server_message;

				switch( client_message ){	
					case "1":
						//Crear
						*server_message = "Por favor digita el nombre de la imagen a crear: ";
						memset(client_message, 0, 2000);
						send(client_sock, client_message, strlen(client_message), 0);
						if(recv(client_sock, client_message, 2000, 0) > 0) {
							printf("received message: %s\n", client_message);
							pthread_create(&tid[cantidadHilos], &attr, worker, &targ[cantidadHilos]); 	
							cantidadHilos++;
						}continue;
						break;
					case "2":
						//Listar
						*server_message = "Listando... ";
						break;
					case "3":
						//Detener
						*server_message = "Por favor digita el nombre de la imagen a detener: ";
						break;
					case "4":
						//Borrar
						*server_message = "Por favor digita el nombre de la imagen a eliminar: ";
						break;
					default:
						break;
				}
				send(client_sock, client_message, strlen(client_message), 0);
			}
		}
    }
	return 0;
}