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

#include "udpclient.h"

#define DEBUG
#define MAX_IP_LENGTH 32

int                socket_desc;
struct sockaddr_in server_addr;
char               server_message[2000], client_message[2000];
unsigned int       server_struct_length = sizeof(server_addr);

int udp_init(char* ip, int port) {
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0) return 1;

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    return 0;
}

int udp_send_data(char* msg) {
    memset(server_message, '\0', sizeof(server_message));

    if (sendto(socket_desc, msg, strlen(msg), 0, (struct sockaddr*)&server_addr, server_struct_length) < 0) {
        printf("Unable to send message\n");
        return 1;
    }

    if (recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr*)&server_addr, &server_struct_length) < 0) {
        printf("Error while receiving server's msg\n");
        return 1;
    }

    return strcmp(server_message, "ACK");
}

void udp_close() {
    close(socket_desc);
}
