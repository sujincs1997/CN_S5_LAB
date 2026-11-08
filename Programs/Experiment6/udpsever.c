#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 8080
#define MAX 1024

// Include your translate() function here
void translate(char *str)
{
    char result[MAX] = "";
    char word[100];
    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        if (isalnum((unsigned char)str[i]))
        {
            j = 0;

            while (isalnum((unsigned char)str[i]) && j < 99)
            {
                word[j++] = tolower((unsigned char)str[i]);
                i++;
            }

            word[j] = '\0';

            const char *replacement = word;

            if (strcmp(word, "tbh") == 0)
                replacement = "to be honest";
            else if (strcmp(word, "idc") == 0)
                replacement = "I don't care";
            else if (strcmp(word, "ig") == 0)
                replacement = "I guess";
            else if (strcmp(word, "tbf") == 0)
                replacement = "to be fair";
            else if (strcmp(word, "atm") == 0)
                replacement = "at the moment";
            else if (strcmp(word, "irl") == 0)
                replacement = "in real life";
            else if (strcmp(word, "lol") == 0)
                replacement = "laughing out loud";
            else if (strcmp(word, "asap") == 0)
                replacement = "as soon as possible";
            else if (strcmp(word, "omg") == 0)
                replacement = "oh my God";
            else if (strcmp(word, "ttyl") == 0)
                replacement = "talk to you later";
            else if (strcmp(word, "idk") == 0)
                replacement = "I don't know";
            else if (strcmp(word, "nvm") == 0)
                replacement = "never mind";

            strcat(result, replacement);
        }
        else
        {
            int len = strlen(result);

            if (len < MAX - 1)
            {
                result[len] = str[i];
                result[len + 1] = '\0';
            }

            i++;
        }
    }

    strcpy(str, result);
}

int main()
{
    int sockfd;
    char buffer[MAX];

    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    printf("UDP Server Running...\n");

    // Receive message from client
    int n = recvfrom(sockfd, buffer, MAX - 1, 0,
                     (struct sockaddr *)&client_addr, &len);

    if (n < 0)
    {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';

    printf("Received: %s\n", buffer);

    // Translate message
    translate(buffer);

    // Send translated message to client
    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&client_addr, len);

    printf("Translated message sent.\n");

    close(sockfd);

    return 0;
}
