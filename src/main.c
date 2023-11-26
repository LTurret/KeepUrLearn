#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>
#include <curl/curl.h>

#include "fetch.c"
#include "getpass.c"
#include "getstid.c"
#include "post.c"
#include "replace.c"
#include "slice.c"

int main(void) {
    // char *stid = get_secret_stid();
    // char *pass = get_secret_pass();

    // cJSON *data = cJSON_CreateObject();
    // cJSON *username = cJSON_CreateString(stid);
    // cJSON *password = cJSON_CreateString(pass);
    // cJSON *captchaCode = cJSON_CreateString("JXPE");
    // cJSON *captchaKey = cJSON_CreateString("2c36c94a-25d3-44af-abdf-904e95cc4bf1");

    // cJSON_AddItemToObject(data, "username", username);
    // cJSON_AddItemToObject(data, "password", password);
    // cJSON_AddItemToObject(data, "captchaCode", captchaCode);
    // cJSON_AddItemToObject(data, "captchaKey", captchaKey);

    // char *string = cJSON_Print(data);
    // printf("%s", string);
    fetch();

    // cJSON_Delete(data);
}
