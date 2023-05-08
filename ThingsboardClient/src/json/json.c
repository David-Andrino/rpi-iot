#include <string.h>
#include <stdint.h>

#include <cjson/cJSON.h>
#include <stdlib.h>
#include "json.h"

int json_generate(char *str, color_t color, acc_t acc) {

    cJSON *object = cJSON_CreateObject();

    cJSON_AddNumberToObject(object, "acc_x", acc.x);
    cJSON_AddNumberToObject(object, "acc_y", acc.y);
    cJSON_AddNumberToObject(object, "acc_z", acc.z);

    cJSON_AddNumberToObject(object, "color_r", color.r);
    cJSON_AddNumberToObject(object, "color_g", color.g);
    cJSON_AddNumberToObject(object, "color_b", color.b);

    char *json_str = cJSON_PrintUnformatted(object);
    strcpy(str, json_str);
    free(json_str);
    cJSON_Delete(object);

    return strlen(str);
}
