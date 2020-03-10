#include "uls.h"

static void checkflag_one(char c, t_flags *flags) {
    if (c == '1') {
        flags->one = true;
        flags->C = false;
        flags->x = false;
        flags->l = false;
        flags->m = false;
    }
    else if (c == 'C') {
        flags->C = true;
        flags->one = false;
        flags->x = false;
        flags->l = false;
        // flags->m = false;
        flags->forcedc = true;
    }
    else if (c == 'c') {
        flags->c = true;
        flags->u = false;
        flags->U = false;
    }
}

static void checkflag_two(char c, t_flags *flags) {
    if (c == 'F') flags->F = true;
    else if (c == 'f') flags->f = true;
    else if (c == 'm') {
        flags->m = true;
        flags->C = false;
        flags->x = false;
        flags->l = false;
        flags->one = false;
    }
    else if (c == 'n') {
        flags->n = true;
        flags->l = true;
    }
    else if (c == 'r') flags->r = true;
    else if (c == 't') flags->t = true;
    else if (c == 'u') {
        flags->u = true;
        flags->c = false;
        flags->U = false;
    }
}

static void checkflag_three(char c, t_flags *flags) {
    if (c == 'R') flags->R = true;
    else if (c == 'U') {
        flags->U = true;
        flags->c = false;
        flags->u = false;
    }
    else if (c == 'x') {
        flags->x = true;
        flags->one = false;
        flags->C = false;
        flags->l = false;
//        flags->m = false;
    }
    else if (c == 'l') {
        flags->l = true;
        flags->C = false;
        flags->x = false;
        flags->one = false;
        flags->m = false;
    }
}

//FILE PRIME FUNCTION
void mx_check_flags(char c, t_flags *flags) {
    checkflag_one(c, flags);
    checkflag_two(c, flags);
    checkflag_three(c, flags);
    if (c == 'A') flags->A = true;
    else if (c == 'p') flags->p = true;
    else if (c == 'S') flags->S = true;
    else if (c == 'G' && isatty(1)) flags->G = true;

}
