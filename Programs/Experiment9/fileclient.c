#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main()
{
 int sockfd;
 struct sockaddr_in server_addr;
 char filename[100];
 char buffer[BUFFER_SIZE];
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(PORT);
 server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
 printf("Enter filename: ");
 scanf("%s", filename);
 send(sockfd, filename, strlen(filename) + 1, 0);
 printf("\nResponse from Server:\n\n");
 while(recv(sockfd, buffer, BUFFER_SIZE - 1, 0) > 0)
 {
 buffer[BUFFER_SIZE - 1] = '\0';
 printf("%s", buffer);
 }
close(sockfd);
return 0 ;
}