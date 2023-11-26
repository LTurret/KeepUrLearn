#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>

char *get_secret_stid() {
    FILE *ptr;
    long len;
    char *content;
    cJSON *json, *stid;

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
        stid = cJSON_GetObjectItemCaseSensitive(json, "student_id");
        if (cJSON_IsString(stid) && (stid->valuestring != NULL)) {
            free(content);
            return stid->valuestring;
        } else {
            fprintf(stderr, "Error when accessing\n");
        }
        cJSON_Delete(json);
    }

    free(content);
    return NULL;
}
