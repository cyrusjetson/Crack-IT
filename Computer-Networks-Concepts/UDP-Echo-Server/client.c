#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sock_id, server_size;
	char msg[30];
	struct sockaddr_in server, client;

	sock_id = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock_id != -1)
		printf("Socket Created Successfully\n");
	else
		printf("Socket Creation Failed\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(8088);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	client.sin_family = AF_INET;
	client.sin_port = htons(8089);
	client.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sock_id, (struct sockaddr*)&client, sizeof(client)) != -1)
		printf("Client Binded Successfully\n");
	else
		printf("Bind Failed\n");

	server_size = sizeof(server);
	do
	{
		printf("Message : ");
		scanf("%s", msg);
		sendto(sock_id, msg, sizeof(msg), 0, (struct sockaddr*)&server, server_size);
		if(strcmp(msg, "exit") == 0)
			break;
		recvfrom(sock_id, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_size);
	}while(strcmp(msg, "exit")!=0);
	close(sock_id);
}