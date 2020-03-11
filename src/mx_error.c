#include "uls.h"

static void free_errors(t_list **errors) {
    t_list *temp_files = *errors;

    while (temp_files) {
        t_list *temp = temp_files;

        temp_files = temp_files->next;
        free(temp->data);
        free(temp);
    }
}

static void invalid_flag_error(char *argument) {
    char *erchar = mx_strndup(argument, 1);

    mx_printerr("illegal option, -- ");
    mx_printerr(erchar);
    mx_printerr("\n");
    mx_printerr("usage: ./uls [-");
    mx_printerr(MX_USED_FLAGS);
    mx_printerr("] [file ...]\n");
    free(erchar);
}

void mx_print_errors_list(t_list *errors) {
    if(errors)
        mx_sort_list(errors, mx_errors_cmp);
    for (t_list *cur = errors; cur; cur = cur->next) {
        char *temp = (char*)cur->data; 
            mx_printerr(temp);
            mx_printerr("\n");
    }
    free_errors(&errors);
}

void mx_error(t_error error_type, char *argument) {
    switch (error_type) {
        case NO_FILE:
            mx_printerr("uls: ");
            mx_printerr(argument);
            mx_printerr(": No such file or directory\n");
            break;
        case ILLEGAL_FLAG:
            invalid_flag_error(argument);
            break;
        default:
            break;
    }
}
