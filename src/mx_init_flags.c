#include "uls.h"

static void dog_to_l_init(t_flags *flags) {
    flags->dog = false;
    flags->one = false;
    flags->A = false;
    flags->a = false;
    flags->B = false;
    flags->b = false;
    flags->C = true;
    flags->c = false;
    flags->d = false;
    flags->e = false;
    flags->F = false;
    flags->f = false;
    flags->G = false;
    flags->g = false;
    flags->H = false;
    flags->h = false;
    flags->i = false;
    flags->k = false;
    flags->L = false;
    flags->l = false;
}

static void m_to_x_init(t_flags *flags) {
    flags->m = false;
    flags->n = false;
    flags->O = false;
    flags->o = false;
    flags->P = false;
    flags-> p = false;
    flags-> q = true;
    flags-> R = false;
    flags-> r = false;
    flags-> S = false;
    flags-> s = false;
    flags-> T = false;
    flags-> t = false;
    flags-> U = false;
    flags-> u = false;
    flags-> v = false;
    flags-> W = false;
    flags-> w = false;
    flags-> x = false;
}

//FILE PRIME FUNCTION!
t_flags *mx_init_flags(void) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));

    dog_to_l_init(flags);
    m_to_x_init(flags);
    return flags;
}
