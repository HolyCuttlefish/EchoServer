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
    int client_socket;
		int bytes_received;

    char bufMess[BUF_SIZE];

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Создание сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
		{
				printf("%s\n", "Socket creation failed");
				return -1;
    }

    // Привязка сокета к адресу
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
		{
      	printf("%s\n","Bind failed");
        close(server_socket);
       	return -1;
    }

    // Прослушивание входящих соединений
    if (listen(server_socket, 5) < 0)
		{
        printf("%s\n","Listen failed");
        close(server_socket);
        return -1;
    }

    // Принятие входящего соединения
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0)
		{
        printf("%s\n","Accept failed");
        close(server_socket);
        return -1;
    }

    // Получение данных от клиента
    bytes_received = recv(client_socket, bufMess, BUF_SIZE, 0);
    if (bytes_received < 0)
		{
        printf("%s\n","Receive failed");
    } else
		{
        // Отправка данных обратно клиенту
        send(client_socket, bufMess, bytes_received, 0);
    }

    // Закрытие сокетов
    close(client_socket);
    close(server_socket);

    return 0;
}
