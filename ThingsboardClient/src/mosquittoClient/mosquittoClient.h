#ifndef MOSQUITTO_H 
#define MOSQUITTO_H

/**
* @brief Send the data via the mosquitto client, configured in a file called credentials.h that must be placed in the same directory as this
* @param data Zero-terminated string that contains the data to be sent
*/
extern void mqtt_send_data(char* data);

#endif
