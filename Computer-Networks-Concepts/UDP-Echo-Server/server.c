#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
 	int sock_id, client_size;
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

	if(bind(sock_id, (struct sockaddr*)&server, sizeof(server)) != -1)
		printf("Server Binded Successfully\n");
	else
		printf("Bind Failed\n");

	client_size = sizeof(client);
	do
	{
		recvfrom(sock_id, msg, sizeof(msg), 0, (struct sockaddr*)&client, &client_size);
		printf("\nMessage Received : %s", msg);
		if(strcmp(msg, "exit")==0)
			break;
		strcpy(msg, "Acknowledged");
		sendto(sock_id, msg, sizeof(msg), 0, (struct sockaddr*)&client, client_size);
	}while(strcmp(msg, "exit")!=0);
	close(sock_id);
}