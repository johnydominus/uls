#include "uls.h"

bool mx_check_flag_validity (char c) {
    char *flags_list = mx_strdup("@1AaBbCcdeFfGgHhikLlmnOoPpqRrSsTtuUvWwx");
    int len = mx_strlen(flags_list);
    bool legal = false;

    for (int i = 0; i < len; ++i) {
        if (c == flags_list[i]) {
            legal = true;
            break;
        }
    }
    free(flags_list);
    if (!legal)
        mx_error(ILLEGAL_FLAG, &c);
    return legal;
}
