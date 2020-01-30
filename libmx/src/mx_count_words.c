#include "libmx.h"

int mx_count_words(const char *str, char delimiter) {
    int flag_word = 0;
    int cntr = 0;

    if(!str)
        return -1;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == delimiter)
            flag_word = 0;
        else {
            if(flag_word == 0)
                ++cntr;
            ++flag_word;
        }
    }
    return cntr;
}
