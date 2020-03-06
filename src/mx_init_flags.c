#include "uls.h"

static void init(t_flags *flags) {
    flags->one = false;
    flags->a = false;
    flags->C = true;
    flags->c = false;
    flags->F = false;
    flags->f = false;
    flags->G = false;
    flags->l = false;
    flags->m = false;
    flags->n = false;
    flags-> p = false;
    flags-> R = false;
    flags-> r = false;
    flags-> S = false;
    flags-> t = false;
    flags-> U = false;
    flags-> u = false;
    flags-> x = false;
    flags->first = true;
    flags->forcedc = false;
}

//FILE PRIME FUNCTION!
t_flags *mx_init_flags(void) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));

    init(flags);
    return flags;
}
