#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    int size_arr = mx_count_words(s, c);
    char **result = malloc(sizeof(char *) * (size_arr + 1));
    int len = 0;
    int i = 0;

    if (!s)
        return NULL;
    for (int j = 0; j < size_arr; ++j) {
        while (s[i] == c && s[i++]) {}
        len = mx_strlen_delim (&s[i], c);
        result[j] = mx_strndup(&s[i], len);
        i += len;
        len = 0;
    }
    result[size_arr] = NULL;
    return result;
}
