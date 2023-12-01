#include "ulearn.h"

#include "delay.c"
#include "update.c"

int main() {
    char cookie[100];
    printf("輸入已登入的session cookie：");
    scanf("%s", cookie);
    printf("\n");
    while (1) {
        update(cookie);
        printf("下一次更新為30秒後\n");
        delay(30000);
    }
}
