#include "ulearn.h"

void update(char *suffix_cookie) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(
            headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36");

        char *url = "https://ulearn.nfu.edu.tw/user/settings#/";
        char prefix_cookie[200] = "session=";

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_COOKIE, strcat(prefix_cookie, suffix_cookie));
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code == 200) {
                printf("更新完成！已保持的session cookie為：\n%s\n\n", suffix_cookie);
            }
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}