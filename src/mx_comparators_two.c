#include "uls.h"

bool mx_alpha_cmp(void *data1, void *data2, bool reverse) {
    t_file *d1 = (t_file*)data1;
    t_file *d2 = (t_file*)data2;

    if (!reverse)
        return (mx_strcmp(d1->d_name, d2->d_name) > 0 ? 1 : 0);
    return (mx_strcmp(d1->d_name, d2->d_name) > 0 ? 0 : 1);
}
