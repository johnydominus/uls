#include "uls.h"

//TODO: static funct for free()

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
            arg = mx_strndup(argument, 1);
            mx_printerr("illegal option, -- ");
            mx_printerr(arg);
            mx_printerr("\n");
            mx_printerr("usage: ./uls [-l] [file ...]\n");
            free(arg);
            exit(1);
            break;
        default:
            break;
    }
    free(arg);
}
