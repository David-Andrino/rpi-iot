#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mosquittoClient.h"
#include "credentials.h"

#define COMMAND_MAX_LENGTH 2000
 
void mqtt_send_data(char* data) {
#ifndef HOSTNAME
    printf("Missing credentials!");
    exit(1);
#endif
#ifndef TOKEN
    printf("Missing credentials!");
    exit(1);
#endif
    char* command = malloc(COMMAND_MAX_LENGTH * sizeof(char));
    sprintf(command, "mosquitto_pub -d -q 1 -h \"%s\" -p \"1883\" -t \"v1/devices/me/telemetry\" -u \"%s\" -m %s", HOSTNAME, TOKEN, data);
#ifndef DEBUG
    system(command);
#else 
    printf("[DEBUG] Command: %s\n", command);
#endif
    free(command);
}
