#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX 20
int main ()
{
int sock = 0;
struct sockaddr_in serv_addr;
int n, matrix[MAX][MAX];
char result[50];
sock = socket(AF_INET, SOCK_STREAM, 0);
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", & serv_addr.sin_addr);
connect(sock, (struct sockaddr *) & serv_addr, sizeof(serv_addr));
printf("Enter order of matrix: ");
scanf("%d", &n);
srand(time(0));
printf("\nGenerated Matrix:\n");
for (int i=0; i<n; i++)
{
for (int j=0; j<n; j++)
{
matrix[i][j] = rand() % 50 + 1;
printf("%4d", matrix[i][j]);
}
printf("\n");
} 
write(sock, &n, sizeof(int));
write(sock, matrix, sizeof(matrix));
read(sock, result, sizeof(result));
printf("\nMatrix Type Received from Server: %s\n", result);
close(sock);
return 0;
}
