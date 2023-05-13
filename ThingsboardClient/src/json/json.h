#ifndef GENERATEJSON_H
#define GENERATEJSON_H

#include "../accelerometer/accelerometer.h"
#include "../colorSensor/colorSensor.h"

/**
* @brief Generate the JSON encoded data for a measurement
* @param str String for the date to be saved in
* @param color Color measurement
* @param acc Acceleration
* @return Length of the saved data
*/
extern int json_generate(char *str, color_t color, acc_t acc);

#endif
