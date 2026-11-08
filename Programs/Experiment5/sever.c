
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 20

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int n, matrix[MAX][MAX];
    char result[50];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    listen(server_fd, 3);

    printf("Waiting for client connection...\n");

    new_socket = accept(server_fd,
                        (struct sockaddr *)&address,
                        (socklen_t *)&addrlen);

    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    read(new_socket, &n, sizeof(int));
    read(new_socket, matrix, n * n * sizeof(int));

    int upper = 1, lower = 1, diagonal = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i > j && matrix[i][j] != 0)
                upper = 0;

            if (i < j && matrix[i][j] != 0)
                lower = 0;

            if (i != j && matrix[i][j] != 0)
                diagonal = 0;
        }
    }

    if (diagonal)
        strcpy(result, "Diagonal Matrix");
    else if (upper)
        strcpy(result, "Upper Triangular Matrix");
    else if (lower)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "Neither Upper nor Lower nor Diagonal");

    write(new_socket, result, sizeof(result));

    printf("Matrix Type Sent to Client: %s\n", result);

    close(new_socket);
    close(server_fd);

    return 0;
}

