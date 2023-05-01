#include <string.h>
#include <stdint.h>

#include "cJSON.h"
#include "json.h"

int json_generate(char *str, color_t *colors, acc_t *accs) {

    cJSON *acc_color = cJSON_CreateObject();
    cJSON_AddItemToObject(acc_color, "Accelerations", cJSON_CreateArray());
    cJSON_AddItemToObject(acc_color, "Colors", cJSON_CreateArray());

    cJON *colors = cJSON_GetObjectItem(acc_color, "Colors");
    cJON *accs = cJSON_GetObjectItem(acc_color, "Accelerations");

    for (int i = 0; i < 10; i++){
        cJSON *color = cJSON_CreateObject();
        cJSON *acc = cJSON_CreateObject();

        cJSON_AddNumberToObject(color, "r", colors[i].r);
        cJSON_AddNumberToObject(color, "g", colors[i].g);
        cJSON_AddNumberToObject(color, "b", colors[i].b);

        cJSON_AddNumberToObject(acc, "x", accs[i].x);
        cJSON_AddNumberToObject(acc, "y", accs[i].y);
        cJSON_AddNumberToObject(acc, "z", accs[i].z);

        cJSON_AddItemToArray(colors,color);
        cJSON_AddItemToArray(accs,acc);
    }

    char *json_str = cJSON_PrintUnformatted(acc_color);
    strcpy(str, json_str);

    cJSON_Delete(acc_color);


    return strlen(str);
}
