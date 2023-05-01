#include <string.h>
#include <stdint.h>

#include "cJSON.h"
#include "json.h"

int generateJSON(char *str, uint8_t r, uint8_t g, uint8_t b, float x, float y, float z) {

    cJSON *acc = cJSON_CreateObject();
    cJSON_AddNumberToObject(acc, "x", x);
    cJSON_AddNumberToObject(acc, "y", y);
    cJSON_AddNumberToObject(acc, "z", z);

    cJSON *color = cJSON_CreateObject();
    cJSON_AddNumberToObject(color, "r", r);
    cJSON_AddNumberToObject(color, "g", g);
    cJSON_AddNumberToObject(color, "b", b);

    cJSON *acc_color = cJSON_CreateObject();
    cJSON_AddItemToObject(acc_color, "Acceleration", acc);
    cJSON_AddItemToObject(acc_color, "Color", color);

    char *tmp = cJSON_Print(acc_color);
    strcpy(str, tmp);
    int len = strlen(str);

    cJSON_Delete(acc_color);

    return len;
}
