#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int sockfd;
void *receive_msg(void *arg)
{
 char message[BUFFER_SIZE];
 while(recv(sockfd, message, BUFFER_SIZE, 0) > 0)
 {
 printf("%s", message);
 }
 return NULL;
}
int main()
{
 struct sockaddr_in server_addr;
 char message[BUFFER_SIZE];
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(PORT);
 inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
 connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
 pthread_t tid; 
 pthread_create(&tid, NULL, receive_msg, NULL);
 while(fgets(message, BUFFER_SIZE, stdin))
 {
 send(sockfd, message, strlen(message), 0);
 }
 close(sockfd);
 return 0;
}