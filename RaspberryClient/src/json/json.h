#ifndef GENERATEJSON_H
#define GENERATEJSON_H

#include "../accelerometer/accelerometer.h"
#include "../colorSensor/colorSensor.h"


/**
* @brief Generate the JSON encoded data for an array of measurements
* @param str String for the date to be saved in
* @param color Color measurement array
* @param acc Acceleration array
* @return Length of the saved data
*/
extern int json_generate(char *str, color_t *colors, acc_t *accs);

#endif
