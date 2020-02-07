#include "uls.h"

static void checkflag_one (char c, t_flags *flags) {
    if(c == '@') flags->dog = true;
    else if (c == '1') {
        flags->one = true;
        flags->C = false;
        flags->x = false;
    }
    else if (c == 'A') flags->A = true;
    else if (c == 'a') flags->a = true;
    else if (c == 'B') {
        flags->B = true;
        flags->b = false;
        flags->w = false;
        flags->q = false;
    }
    else if (c == 'b') {
        flags->b = true;
        flags->B = false;
        flags->w = false;
        flags->q = false;
    }
}

static void checkflag_two (char c, t_flags *flags) {
    if (c == 'C') {
        flags->C = true;
        flags->one = false;
        flags->x = false;
    }
    else if (c == 'c') {
        flags->c = true;
        flags->u = false;
    }
    else if (c == 'd') flags->d = true;
    else if (c == 'e') flags->e = true;
    else if (c == 'F') flags->F = true;
    else if (c == 'f') flags->f = true;
    else if (c == 'G') flags->G = true;
    else if (c == 'g') flags->g = true;
    else if (c == 'H') flags->H = true;
    else if (c == 'h') flags->h = true;
    else if (c == 'i') flags->i = true;
    else if (c == 'k') flags->k = true;
    else if (c == 'l') flags->l = true;
}

static void checkflag_three (char c, t_flags *flags) {
    if (c == 'L') {
        flags->L = true;
        flags->P = false;
    }
    else if (c == 'm') flags->m = true;
    else if (c == 'n') flags->n = true;
    else if (c == 'O') flags->O = true;
    else if (c == 'o') flags->o = true;
    else if (c == 'P') {
        flags->P = true;
        flags->H = false;
        flags->L = false;
    }
    else if (c == 'p') flags->p = true;
    else if (c == 'q') {
        flags->q = true;
        flags->B = false;
        flags->b = false;
        flags->w = false;
    }
}

static void checkflag_four (char c, t_flags *flags) {
    if (c == 'R') flags->R = true;
    else if (c == 'r') flags->r = true;
    else if (c == 'S') flags->S = true;
    else if (c == 's') flags->s = true;
    else if (c == 'T') flags->T = true;
    else if (c == 't') flags->t = true;
    else if (c == 'u') {
        flags->u = true;
        flags->c = false;
    }
    else if (c == 'U') flags->U = true;
    else if (c == 'v') flags->v = true;
    else if (c == 'W') flags->W = true;
    else if (c == 'w') {
        flags->w = true;
        flags->B = false;
        flags->b = false;
        flags->q = false;
    }
}

//FILE PRIME FUNCTION!
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags) {
    for (; *i < argc; ++(*i)) {
        if (argv[*i][0] == '-') {
            int len = mx_strlen(argv[*i]);

            for (int j = 1; j < len; ++j) {
                checkflag_one (argv[*i][j], flags);
                checkflag_two (argv[*i][j], flags);
                checkflag_three (argv[*i][j], flags);
                checkflag_four (argv[*i][j], flags);
                if (argv[*i][j] == 'x') {
                    flags->x = true;
                    flags->one = false;
                    flags->C = false;
                }
                mx_check_flag_validity(argv[*i][j]);
            }
        }
        else
            break;
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
