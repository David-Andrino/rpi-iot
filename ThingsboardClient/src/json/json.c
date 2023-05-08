#include <string.h>
#include <stdint.h>

#include <cjson/cJSON.h>
#include <stdlib.h>
#include "json.h"

int json_generate(char *str, color_t color, acc_t acc) {

    cJSON *object = cJSON_CreateObject();

    cJSON *accJSON = cJSON_CreateObject();
    cJSON_AddNumberToObject(accJSON, "x", acc.x);
    cJSON_AddNumberToObject(accJSON, "y", acc.y);
    cJSON_AddNumberToObject(accJSON, "z", acc.z);
    cJSON_AddItemToObject(object, "acceleration", accJSON);

    cJSON *colorJSON = cJSON_CreateObject();
    cJSON_AddNumberToObject(colorJSON, "r", color.r);
    cJSON_AddNumberToObject(colorJSON, "g", color.g);
    cJSON_AddNumberToObject(colorJSON, "b", color.b);
    cJSON_AddItemToObject(object, "color", colorJSON);

    char *json_str = cJSON_PrintUnformatted(object);
    strcpy(str, json_str);
    free(json_str);
    cJSON_Delete(object);

    return strlen(str);
}
