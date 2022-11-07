#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sock_id, bind_status, accept_status;
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

	bind_status = bind(sock_id, (struct sockaddr*)&server, sizeof(server));
	if(bind_status != -1)
		printf("Binded Successfully\n");
	else
		printf("Bind Failed\n");

	listen(sock_id, 3);

	int client_size = sizeof(client);
	do
	{
		accept_status = accept(sock_id, (struct sockaddr*)&client, &client_size);
		if(accept_status != -1)
			printf("\nClient Accepted\n");
		else
			printf("\nClient Accept Failed\n");
		if(fork()==0)//child
		{
			do
			{
				recv(accept_status, msg, sizeof(msg), 0);
				if(strcmp(msg, "EXIT") == 0)
					break;
				printf("Received Message : %s\n", msg);
				printf("Message to send: ");
				scanf("%s", msg);
				send(accept_status, msg, sizeof(msg), 0);
				if(strcmp(msg, "SHUTDOWN") == 0)
					exit(0);
			}while(strcmp(msg, "EXIT") != 0);
		}
		printf("Client Closed\n");
	}while(strcmp(msg, "SHUTDOWN") != 0);	//close server till SHUTDOWN message from server
	close(sock_id);
}