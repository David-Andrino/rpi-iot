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

    color_t color;
    acc_t   acc;
    while (!stop) {
        acc_read(&acc);
        cs_read_clear_corrected(&color);
        char tmp[2000];
        json_generate(tmp, color, acc);
        mqtt_send_data(tmp);
        sleep(1);
    }

    // Close the file descriptors
    acc_close();
    cs_close();
}
