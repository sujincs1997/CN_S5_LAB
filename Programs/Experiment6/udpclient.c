#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main()
{
    int sockfd;
    char message[MAX];
    char buffer[MAX];

    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Get message from user
    printf("Enter sentence:\n");
    fgets(message, MAX, stdin);

    // Send message to server
    sendto(sockfd, message, strlen(message) + 1, 0,
           (struct sockaddr *)&server_addr, len);

    // Receive translated message
    int n = recvfrom(sockfd, buffer, MAX - 1, 0,
                     (struct sockaddr *)&server_addr, &len);

    if (n < 0)
    {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';

    printf("\nTranslated Sentence:\n%s\n", buffer);

    close(sockfd);

    return 0;
}

