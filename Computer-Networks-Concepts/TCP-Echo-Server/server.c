#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
	int sock_id, bind_status, accept_id, client_size;
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

	client_size = sizeof(client);

	bind_status = bind(sock_id, (struct sockaddr*)&server, sizeof(server));
	if(bind_status != -1)
		printf("Binded Successfully\n");
	else
		printf("Bind Failed\n");

	listen(sock_id, 1);

	accept_id = accept(sock_id, (struct sockaddr*)&client, &client_size);
	if(accept_id != -1)
		printf("Accepted Successfully\n");
	else
		printf("Accept Failed\n");

	do
	{
		recv(accept_id, msg, sizeof(msg), 0);
		printf("Message From Client : %s\n", msg);
		strcpy(msg, "Acknowledged");
		send(accept_id, msg, sizeof(msg), 0);
	}while(strcmp(msg, "exit")!=0);
	close(accept_id);
}