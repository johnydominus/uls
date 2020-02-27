#include "uls.h"

//TODO: static funct for free_all()

static void illegal_flag (char *argument, char* temp_arg) {
    temp_arg = mx_strndup(argument, 1);
    mx_printerr("illegal option, -- ");
    mx_printerr(temp_arg);
    mx_printerr("\n");
    mx_printerr("usage: ./uls [-l] [file ...]\n");
    free(temp_arg);          //free_all() here!
    exit(1);
}

void mx_error(t_error error_type, char *argument) {
    if (TEST) printf(">mx_error\n");
    char *arg = NULL;

    switch (error_type) {
        case NO_FILE:
            arg = mx_strdup(argument);
            mx_printerr("uls: ");
            mx_printerr(arg);
            mx_printerr(": No such file or directory\n");
            break;
        case ILLEGAL_FLAG:
            illegal_flag(argument, arg);
            break;
        default:
            break;
    }
    free(arg);
}
