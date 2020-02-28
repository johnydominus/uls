#include "uls.h"



//FILE PRIME FUNCTION!
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags) {
    for (; *i < argc; ++(*i)) {
        if (argv[*i][0] == '-' && argv[*i][1]) {
            int len = mx_strlen(argv[*i]);

            for (int j = 1; j < len; ++j) {
                mx_check_flags(argv[*i][j], flags);
                if (argv[*i][j] == 'x') {
                    flags->x = true;
                    flags->one = false;
                    flags->C = false;
                }
                mx_check_flag_validity(argv[*i][j]);
            }
        }
        else {
            --(*i);
            break;
        }
    }
}

//ALL FLAGS
//@1AaBbCcdeFfGgHhikLlmnOoPpqRrSsTtuUvWwx

//OVERLAPING
// 1 C x
// c u
// B b w q
// H L P

//TERMINAL DEFAULT
// C q

//SUPER-USER DEFAULT
// A

//DONE:
// A a p

//IN PROGRESS:
// F R C 1 x r l
