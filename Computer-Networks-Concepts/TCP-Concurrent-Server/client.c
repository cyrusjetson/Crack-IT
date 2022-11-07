#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sock_id, bind_status, connect_status;
	struct sockaddr_in server, client;
	char msg[30];

	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_id != -1)
		printf("Socket Created\n");
	else
		printf("Socket Creation Failed\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(8081);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	connect_status = connect(sock_id, (struct sockaddr*)&server, sizeof(server));
	if(connect_status != -1)
		printf("Connected Successfully\n");
	else
		printf("Connection Failed\n");

	do
	{
		printf("Message to send : ");
		scanf("%s", msg);
		send(sock_id, msg, sizeof(msg), 0);
		if(strcmp(msg, "EXIT") == 0)	//close this client
			break;
		recv(sock_id, msg, sizeof(msg), 0);
		if(strcmp(msg, "SHUTDOWN") == 0)	//close client since server is closed
			break;
		printf("Received Message : %s\n", msg);
	}while(strcmp(msg, "EXIT") != 0);
	close(sock_id);
}