#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

int main(int argc, char *argv[]) {
	int sock;
	struct sockaddr_in server;
	char message[1000], server_reply[2000];
	
	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//Connect to remote server
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");

	while(1)
	{
		printf( "Menu:\n\n 1.Crear Contenedor\n2.Listar Contenedores\n3. Detener Contenedores\n4. Borrar Contenedor\n--> " );
		fgets(message, 1000, stdin);
		message[strcspn(message, "\n")] = 0;
		printf("mensaje a enviar: %s\n", message);
		
		//Send some data
		if (send(sock, message, strlen(message)+1, 0) < 0) {
			puts("Send failed");
			return 1;
		} else {
			puts("send ok");
		}

		//Receive a reply from the server
		memset(server_reply, 0, 2000);
		if (recv(sock, server_reply, 2000, 0) < 0) {
			puts("recv failed");
			//break;
		} else {
			puts("recv ok");
		}
		
		puts("Server reply :");
		puts(server_reply);
		fgets(message, 1000, stdin);
		message[strcspn(message, "\n")] = 0;
		if (send(sock, message, strlen(message)+1, 0) < 0) {
			puts("Send failed");
			return 1;
		} else {
			puts("send ok");
		}
		/*switch( message ){	
			case "1":
				//Crear
				break;
			case "2":
				//Listar
				break;
			case "3":
				//Detener
				break;
			case "4":
				//Borrar
				break;
			default:
				break;
		}*/		

		printf("mensaje a enviar: %s\n", message);
		
	}
	close(sock);
	return 0;
}