#include <stdio.h>
#include <string.h>

void slice(const char *str, char *result, size_t start, size_t end) { strncpy(result, str + start, end - start); }