#include <curl/curl.h>
#include <stdio.h>

void post(char *url, char *data, struct curl_slist *out_cookies) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *cookies = NULL;
    struct curl_slist *headers = NULL;
    struct curl_slist *nc;
    int i;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        // curl_easy_setopt(curl, CURLOPT_NOBODY, 1);            // stop printing out
        // curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");          // setting cookie jar
        curl_easy_setopt(curl, CURLOPT_COOKIELIST, out_cookies); // place cookies

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
            if (res != CURLE_OK) {
                fprintf(stderr, "Curl getinfo failed: %s\n", curl_easy_strerror(res));
            } else {
                nc = cookies;
                i = 1;
                while (nc) {
                    printf("[%d]: %s\n", i, nc->data);
                    nc = nc->next;
                    i++;
                }
            }
        }

        curl_easy_cleanup(curl);

        if (cookies) {
            curl_slist_free_all(cookies);
        }
    }

    curl_global_cleanup();
}
