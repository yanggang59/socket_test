#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址信息
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <=

 0) {
        perror("Failed to set server IP");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", SERVER_IP, SERVER_PORT);

    // 发送数据
    strcpy(buffer, "Hello, Server!");
    if (send(clientSocket, buffer, strlen(buffer), 0) == -1) {
        perror("Failed to send data");
        exit(EXIT_FAILURE);
    }

    // 接收响应
    memset(buffer, 0, sizeof(buffer));
    if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("Failed to receive data");
        exit(EXIT_FAILURE);
    }

    printf("Server response: %s\n", buffer);

    // 关闭套接字
    close(clientSocket);

    return 0;
}
