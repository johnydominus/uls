#include "uls.h"

static void init(t_flags *flags) {
    flags->one = false;
    flags->A = false;
    flags->C = true;
    flags->c = false;
    flags->G = false;
    flags->l = false;
    flags->m = false;
    flags->R = false;
    flags->r = false;
    flags->S = false;
    flags->t = false;
    flags->U = false;
    flags->u = false;
    flags->x = false;
    flags->first = true;
    flags->forcedc = false;
    flags->printpath = false;
}

t_flags *mx_init_flags(void) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));

    init(flags);
    return flags;
}
