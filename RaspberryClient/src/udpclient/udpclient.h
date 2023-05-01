#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include <stdint.h>
/**
 * @brief Module to take care of the UDP communications
 * @author David Andrino & Fernando Sanz
 */

/**
 * @brief Initialize the UDP client socket
 * @param ip Server's ip address
 * @param port Server's service port
 * @return 0 if the initialization was successfull, else 1
 */
extern int udp_init(char* ip, int port);

/**
 * @brief Send a data packet in the udp socket
 * @param msg Null terminated message string
 * @return 0 if the pdu is ack'd, else 1
 */
extern int udp_send_data(char* msg);

/**
 * @brief Close the UDP communication socket
 */
extern void udp_close();

#endif
