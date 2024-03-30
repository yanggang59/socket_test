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
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    char buffer[BUFFER_SIZE];

    // 创建服务端套接字
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址信息
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 绑定套接字到指定地址和端口
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    // 接收数据
    clientAddrLen = sizeof(clientAddr);
    memset(buffer, 0, sizeof(buffer));
    if (recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
        perror("Failed to receive data");
        exit(EXIT_FAILURE);
    }

    printf("Client message: %s\n", buffer);

    // 发送响应
    strcpy(buffer, "Hello, Client!");
    if (sendto(serverSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddr, clientAddrLen) == -1) {
        perror("Failed to send data");
        exit(EXIT_FAILURE);
    }

    // 关闭套接字
    close(serverSocket);

    return 0;
}
