#include "uls.h"

static void daddy_love_auditor(t_daddy *daddy) {
    int num_of_dig = 1;

    for (int largest = daddy->size; largest > 0; largest /= 10)
        num_of_dig++;
    daddy->size = num_of_dig;
    num_of_dig = 1;
    for (int largest = daddy->n_link; largest > 0; largest /= 10)
        num_of_dig++;
    daddy->n_link = num_of_dig;
    if (daddy->ma_size != 0) {
        if (daddy->ma_size < 4)
            daddy->ma_size = 4;
        if (daddy->size > 8)
            daddy->ma_size += daddy->size - 8;
        else
            daddy->size = 9;
    }
}

static void fuck_auditor(t_file *file, t_daddy *daddy) {
    long major = ((int)(((unsigned int)file->stat.st_rdev >> 24) & 0xff));
    long size = 0;

    for (; major > 0; major /= 10)
        size++;
    if (major == 0)
        size++;
    if (daddy->ma_size < size)
        daddy->ma_size = size;
}

static t_daddy who_the_daddy(t_list *files) {
    t_daddy daddy;

    mx_set_daddy(&daddy);
    for (t_list *cur = files; cur; cur = cur->next) {
        daddy.total += ((t_file*)cur->data)->stat.st_blocks;
        if (((t_file*)cur->data)->stat.st_size > daddy.size)
            daddy.size = ((t_file*)cur->data)->stat.st_size;
        if (mx_which_file((t_file*)cur->data) == 'b' ||
            mx_which_file((t_file*)cur->data) == 'c')
            fuck_auditor(((t_file*)cur->data), &daddy);
        if (((t_file*)cur->data)->stat.st_nlink > daddy.n_link)
            daddy.n_link = ((t_file*)cur->data)->stat.st_nlink;
        if (mx_strlen_own(((t_file*)cur->data)) > daddy.own_name)
            daddy.own_name  = mx_strlen_own(((t_file*)cur->data));
        if (mx_strlen_grp(((t_file*)cur->data)) > daddy.grp_name)
            daddy.grp_name = mx_strlen_grp(((t_file*)cur->data));
    }
    daddy_love_auditor(&daddy);
    return daddy;
}

/*
*if(MX_ISLNK(((t_file*)files->data)->stat.st_size) == true) {
*    mx_printstr("tut\n");
*}
* Why it does not work??
*/

static void print_total(t_list *files, long total, t_flags *flags) {
    if (flags->file_args == true)
        return;
    if (files != NULL) {
        if (mx_which_file((t_file*)files->data) == 'l'
            && files->next == NULL)
            return;
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
    }
}

void mx_print_long_format(t_list *files, t_flags *flags) {
    if (flags->l == true) {
        t_daddy daddy = who_the_daddy(files);

        print_total(files, daddy.total, flags);
        for (t_list *cur = files; cur; cur = cur->next) {
            t_file *temp = (t_file*)cur->data;
            mx_file_mode(temp);
            mx_print_with_tabl(temp->stat.st_nlink, daddy.n_link, false);
            mx_user_group(temp, &daddy);
            if (mx_which_file(temp) == 'b' || mx_which_file(temp) == 'c')
                mx_print_major_minor(temp, daddy.ma_size);
            else
                mx_print_with_tabl(temp->stat.st_size, daddy.size, false);
            mx_printstr(" ");
            mx_print_time(temp, flags);
            mx_print_filename(temp, flags);
            mx_print_link(temp);
            mx_printstr("\n");
        }
    }
}
