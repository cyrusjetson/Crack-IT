#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int sock_id, bind_status;
	struct sockaddr_in server, client;

	sock_id = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock_id != -1)
		printf("Socket Created Successfully\n");
	else
		printf("Socket Creation Failed\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(8081);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	client.sin_family = AF_INET;
	client.sin_port = htons(8080);
	client.sin_addr.s_addr = htonl(INADDR_ANY);

	bind_status = bind(sock_id, (struct sockaddr*)&client, sizeof(client));
	if(bind_status != -1)
		printf("Bind Successfull\n");
	else
		printf("Bind Failed\n");

	if(fork()==0)//child
	{
		char msg[30];
		int server_size =  sizeof(server);
		do
		{
			recvfrom(sock_id, msg, sizeof(msg), 0, (struct sockaddr*)&server, &server_size);
			printf("Received : %s\n", msg);
		}while(strcmp(msg, "exit") != 0);
		close(sock_id);
	}
	else	//parent
	{
		char msg[30];
		do
		{
			scanf("%s", msg);
			sendto(sock_id, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server));
		}while(strcmp(msg, "exit") != 0);
		close(sock_id);
	}
}