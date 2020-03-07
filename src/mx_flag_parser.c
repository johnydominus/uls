#include "uls.h"

void mx_flag_parser(int *i, int argc, char **argv, t_flags *flags) {
    for (; *i < argc; ++(*i)) {
        if (!mx_strcmp(argv[*i], "--")) {
            ++i;
            break;
        }
        if (argv[*i][0] == '-' && argv[*i][1] && argv[*i][1] != ' ') {
            int len = mx_strlen(argv[*i]);

            for (int j = 1; j < len; ++j) {
                if (mx_check_flag_validity(argv[*i][j]) == false) {
                    free(flags);
                    exit(1);
                }
                mx_check_flags(argv[*i][j], flags);
            }
        }
        else
            break;
    }
}
