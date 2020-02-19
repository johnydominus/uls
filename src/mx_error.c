#include "uls.h"

//TODO: static funct for free()

void mx_error(t_error error_type, char *argument) {
    char *arg = mx_strndup(argument, 1);
    
    switch (error_type) {
        case NO_FILE:
            mx_printerr("uls: ");
            mx_printerr(arg);
            mx_printerr(": No such file or directory\n");
            break;
        case ILLEGAL_FLAG:
            mx_printerr("illegal option, -- ");
            mx_printerr(arg);
            mx_printerr("\n");
            mx_printerr("usage: ./uls [-l] [file ...]\n");
            exit(1);
            break;
        default:
            break;
    }
    free(arg);
}
