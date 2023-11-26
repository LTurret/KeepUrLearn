#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>

char *get_secret_pass() {
    FILE *ptr;
    long len;
    char *content;
    cJSON *json, *password;

    ptr = fopen("../.secret.json", "rb");

    if (ptr == NULL) {
        printf("file can't be open.\n");
    }

    fseek(ptr, 0, SEEK_END);
    len = ftell(ptr);
    fseek(ptr, 0, SEEK_SET);

    content = (char *)malloc(len + 1);
    if (content == NULL) {
        perror("Error allocating memory");
    }

    fread(content, 1, len, ptr);
    fclose(ptr);

    json = cJSON_Parse(content);
    if (json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
    } else {
        password = cJSON_GetObjectItemCaseSensitive(json, "password");
        if (cJSON_IsString(password) && (password->valuestring != NULL)) {
            free(content);
            return password->valuestring;
        } else {
            fprintf(stderr, "Error when accessing\n");
        }
        cJSON_Delete(json);
    }

    free(content);
    return NULL;
}
