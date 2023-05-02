#include <string.h>
#include <stdint.h>

#include "cJSON.h"
#include "json.h"

int json_generate(char *str, color_t *colors, acc_t *accs) {

    cJSON *acc_color = cJSON_CreateArray();

    for (int i = 0; i < 10; i++){
        cJSON *sample = cJSON_CreateObject();

        cJSON_AddNumberToObject(sample, "Sample", i);

        cJSON *acc = cJSON_CreateObject();
        cJSON_AddNumberToObject(acc, "x", accs[i].x);
        cJSON_AddNumberToObject(acc, "y", accs[i].y);
        cJSON_AddNumberToObject(acc, "z", accs[i].z);
        cJSON_AddItemToObject(sample, "Acceleration", acc);

        cJSON *color = cJSON_CreateObject();
        cJSON_AddNumberToObject(color, "r", colors[i].r);
        cJSON_AddNumberToObject(color, "g", colors[i].g);
        cJSON_AddNumberToObject(color, "b", colors[i].b);
        cJSON_AddItemToObject(sample, "Color", color);

        cJSON_AddItemToArray(acc_color, sample);

    }

    char *json_str = cJSON_Print(acc_color);
    strcpy(str, json_str);
    free(json_str);
    cJSON_Delete(acc_color);

    return strlen(str);
}
