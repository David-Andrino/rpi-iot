/**
 * @brief Basic Raspberry Pi udp client. Connects to the server and sends the readings as JSON text
 * @author David Andrino & Fernando Sanz
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "accelerometer/accelerometer.h"
#include "colorSensor/colorSensor.h"
#include "json/json.h"
#include "mosquittoClient/mosquittoClient.h"

volatile int stop = 0;

void sigint_isr(int s) {
    stop = 1;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s IP PORT", argv[0]);
        return -1;
    }

    signal(SIGINT, sigint_isr);

    // Initialize sensors and clients
    acc_init();
    cs_init();

    color_t color[10];
    acc_t   acc[10];
    while (!stop) {
        for (int i = 0; i < 10; i++) {
            // Read data 10 times, waiting 1 second
            acc_read(&(acc[i]));
            cs_read_clear_corrected(&(color[i]));
            sleep(1);
        }
        // Send data to UDP server
        for (int i = 0; i < 10; i++) {
            char tmp[2000];
            json_generate(tmp, color, acc);
            mqtt_send_data(tmp);
        }


    }

    // Close the file descriptors
    acc_close();
    cs_close();
}
