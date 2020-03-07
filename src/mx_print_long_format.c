#include "uls.h"

long count_num_of_dig(t_list *files, int cmp) {
    long num_of_dig = 1;
    off_t largest = 0;

    for (t_list *cur = files; cur; cur = cur->next) {
        if (cmp == 0) {
            if (((t_file*)cur->data)->stat.st_size > largest)
                largest = ((t_file*)cur->data)->stat.st_size;
        }
        else {
            if (((t_file*)cur->data)->stat.st_nlink > largest)
                largest = ((t_file*)cur->data)->stat.st_size;
        }
    }
    for (; largest > 0; largest /= 10)
        num_of_dig *= 10;
    return num_of_dig;
}

void mx_print_with_tabl(long num, long num_of_dig) {
    for (; num / num_of_dig == 0; num_of_dig /= 10)
        mx_printchar(' ');
    mx_printint(num);
}

void mx_print_long_format(t_list *files, t_flags *flags) {
    if (flags->l == true) {
        long num_of_dig_size= count_num_of_dig(files, 0);
        long num_of_dig_link = count_num_of_dig(files, 1) / 10;  // To avoid excessive space

        for (t_list *cur = files; cur; cur = cur->next) {
            t_file *temp = (t_file*)cur->data; 
            mx_file_mode(temp);
            mx_print_with_tabl(temp->stat.st_nlink, num_of_dig_link);
            mx_user_group(temp, flags);
            mx_print_with_tabl(temp->stat.st_size, num_of_dig_size);
            mx_printstr(" ");
            mx_print_time(temp);
            mx_printstr(temp->d_name);
            mx_printstr("\n");
        }
    }
}
