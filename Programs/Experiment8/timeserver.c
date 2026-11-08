#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main() {
 int sockfd;
 char buffer[BUFFER_SIZE];
 struct sockaddr_in server_addr, client_addr;
 socklen_t len;
 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 server_addr.sin_family = AF_INET;
 server_addr.sin_addr.s_addr = INADDR_ANY;
 server_addr.sin_port = htons(PORT);
 bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
 printf("UDP Time Server Running...\n");
 while(1) {
 len = sizeof(client_addr);
 recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &len);
 time_t current_time;
 time(&current_time);
 strcpy(buffer, ctime(&current_time));
 sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, len);
 }
 close(sockfd);
 return 0;
}