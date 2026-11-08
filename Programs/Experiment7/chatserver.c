#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t lock;
void broadcast(char *message, int sender) {
 pthread_mutex_lock(&lock);
 for (int i = 0; i < client_count; i++) {
 if (clients[i] != sender) {
 send(clients[i], message, strlen(message), 0);
 }
 }
 pthread_mutex_unlock(&lock);
}
void *handle_client(void *arg) {
 int client_socket = *(int *)arg;
 char buffer[BUFFER_SIZE];
 int len;
 while ((len = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
 buffer[len] = '\0';
 broadcast(buffer, client_socket);
 }
 close(client_socket);
 pthread_exit(NULL);
}
int main() {
 int server_fd, client_socket;
 struct sockaddr_in server_addr, client_addr;
 socklen_t addr_size;
 pthread_mutex_init(&lock, NULL);
 server_fd = socket(AF_INET, SOCK_STREAM, 0);
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(PORT);
 server_addr.sin_addr.s_addr = INADDR_ANY;
 bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
 listen(server_fd, 5);
 printf("Server running on port %d\n", PORT);
 while (1)
 {
 addr_size = sizeof(client_addr);
 client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
 clients[client_count++] = client_socket;
 pthread_t tid;
 pthread_create(&tid, NULL, handle_client, &clients[client_count - 1]);
 } 
 close(server_fd);
 return 0;
}