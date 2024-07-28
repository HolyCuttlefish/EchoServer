#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	int server_socket;
	int bytes_received;

	char bufMess[BUF_SIZE] = "Hello, my first echo-server!";
	char receivedData[BUF_SIZE];

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(2000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//Создание сокета
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket < 0)
	{
		printf("%s\n", "Spcket creation failed");
		return -1;
	}

	//Соединяемся с сокетом
	if(connect(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
	{
		printf("%s\n","There was an error making a connection to the remote socket");
		close(server_socket);
		return -1;
	}

	//Отправка данных серверу
	send(server_socket, &bufMess, BUF_SIZE, 0);

	//Полученние данных от сервера
	bytes_received = recv(server_socket, &receivedData, BUF_SIZE, 0);
	if(bytes_received < 0)
	{
		printf("%s\n", "Receive failed");
	} else
	{
		printf("%s\n", receivedData);
	}

	close(server_socket);

	return 0;
}
