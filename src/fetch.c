#include <regex.h>
#include <stdio.h>

#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void fetch() {
    regex_t regex;
    regmatch_t pmatch[1];
    int success = regcomp(&regex, "action=\"(\\S+)\"", REG_EXTENDED);

    if (success) {
        fprintf(stderr, "compile err\n");
    }

    struct MemoryStruct chunk;
    struct curl_slist *cookies = NULL;
    struct curl_slist *nc;

    char url[] = "https://identity.nfu.edu.tw/auth/realms/nfu/protocol/cas/login?service=https://ulearn.nfu.edu.tw/login";

    CURL *session;
    CURLcode res;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    session = curl_easy_init();

    if (session) {

        curl_easy_setopt(session, CURLOPT_URL, url);
        curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(session, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(session, CURLOPT_COOKIEFILE, "");

        res = curl_easy_perform(session);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            res = curl_easy_getinfo(session, CURLINFO_COOKIELIST, &cookies);
            if (res != CURLE_OK) {
                fprintf(stderr, "Curl getinfo failed: %s\n", curl_easy_strerror(res));
            } else {
                nc = cookies;
                int i = 1;
                while (nc) {
                    printf("[%d]: %s\n", i, nc->data);
                    nc = nc->next;
                    i++;
                }
            }
        }

        curl_easy_cleanup(session);
    }

    curl_global_cleanup();

    if (regexec(&regex, chunk.memory, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        size_t size = end - start;
        char *match = malloc(size + 1);
        strncpy(match, &chunk.memory[start], size);
        match[size] = '\0';

        char *replaced = replace(match, "&amp;", "&");
        char url[225];
        slice(replaced, url, 8, 221);
        printf("%s\n", url);
        char *data = "username=41143263&password=LTB@nana28592219&captchaCode=MBCw&captchaKey=c58caca0-08bd-4c2c-861b-d52a8826ffbe";
        post(url, data, cookies);

        free(match);
    } else {
        printf("No match\n");
    }
    regfree(&regex);
    free(chunk.memory);
}