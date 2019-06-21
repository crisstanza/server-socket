#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("[ERROR] Usage: %s port-number\n", argv[0]);
		return 1;
	}

	int pSize = 4096;

	int socket_desc, client_sock, c, read_size, serverPort;
	struct sockaddr_in server, client;
	char client_message[pSize];

	serverPort = atoi(argv[1]);
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if ( socket_desc == -1 ) {
		printf("[ERROR] Could not create socket.\n");
		return 2;
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(serverPort);
	
	if ( bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0 ) {
		printf("[ERROR] Bind failed.\n");
		return 3;
	}

	printf("[OK] Socket created and bind done.\n");
	listen(socket_desc, 3);
	printf("[INFO] Listenning at port %d.\n\n", serverPort);
	
	c = sizeof(struct sockaddr_in);
	
	while(1)	 {
		client_sock = accept( socket_desc, (struct sockaddr *) &client, (socklen_t*) &c );
		if (client_sock < 0) {
			printf("[ERROR] Accept failed.\n");
			return 4;
		}
		printf("[OK] Connection accepted.\n");
		memset(client_message, 0, pSize);
		while(read_size = recv(client_sock, client_message, pSize, 0) > 0) {
			printf("[INFO] Size: %d.\n", strlen(client_message));
			write(client_sock, client_message, strlen(client_message));
		}
		if (read_size == 0) {
			printf("[OK] Client disconnected.\n\n");
		} else if(read_size == -1) {
			printf("[ERROR] Receive failed.\n\n");
		}
		fflush(stdout);
	}

	return 0;
}
