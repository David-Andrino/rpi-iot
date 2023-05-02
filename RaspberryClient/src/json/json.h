#ifndef GENERATEJSON_H
#define GENERATEJSON_H

#include "../accelerometer/accelerometer.h"
#include "../colorSensor/colorSensor.h"

extern int json_generate(char *str, color_t *colors, acc_t *accs);

#endif
