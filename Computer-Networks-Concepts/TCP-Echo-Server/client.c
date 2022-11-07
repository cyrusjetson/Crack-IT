#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sock_id;
	char msg[30];
	struct sockaddr_in server, client;

	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_id != -1)
		printf("Socket Created Successfully\n");
	else
		printf("Socket Creation Failed\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(8081);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(sock_id, (struct sockaddr*)&server, sizeof(server)) != -1)
		printf("Connected Successfully\n");
	else
		printf("Connection Failed\n");

	do
	{
		printf("Message : ");
		scanf("%s", msg);
		send(sock_id, msg, sizeof(msg), 0);
		if(strcmp(msg, "exit")==0)
			break;
		recv(sock_id, msg, sizeof(msg), 0);
		printf("Acknowledged\n");
	}while(strcmp(msg, "exit")!=0);
	close(sock_id);
}