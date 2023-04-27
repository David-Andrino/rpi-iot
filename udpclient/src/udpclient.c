/**
 * @brief Basic C UDP client
 * @author David Andrino & Fernando Sanz
 */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define MAX_IP_LENGTH 32

int main(void) {
    int                socket_desc;
    struct sockaddr_in server_addr;
    char               server_message[2000], client_message[2000];
    unsigned int       server_struct_length = sizeof(server_addr);

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    int  port;
    char ip[MAX_IP_LENGTH];
    fflush(stdin);
    printf("Enter server ip: ");
    if (!scanf("%31[^\n]", ip)) return 1;
    fflush(stdin);
    printf("Enter server port: ");
    if (!scanf("%d", &port)) return 1;
    fflush(stdin);
#ifdef DEBUG
    printf("[DEBUG] Connecting to: %s:%d\n", ip, port);
#endif

    // Set port and IP:
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

#ifdef DEBUG
    printf("[DEBUG] Created struct successfully\n");
#endif
    // Get input from the user:
    // printf("Enter message: ");
    // if (!scanf("%1999[^\n]", client_message)) return 1;
    strcpy(client_message, "TEST MESSAGE");

    // Send the message to server:
    if (sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr *)&server_addr, server_struct_length) < 0) {
        printf("Unable to send message\n");
        return -1;
    }

    // Receive the server's response:
    if (recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_addr, &server_struct_length) < 0) {
        printf("Error while receiving server's msg\n");
        return -1;
    }

    printf("Server's response: %s\n", server_message);

    // Close the socket:
    close(socket_desc);

    return 0;
}
