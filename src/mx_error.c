#include "uls.h"

//TODO: static funct for free()
void mx_error(t_error error_type, char *argument) {
    char *erchar = NULL;
    switch (error_type) {
        case NO_FILE:
            mx_printerr("uls: ");
            mx_printerr(argument);
            mx_printerr(": No such file or directory\n");
            break;
        case ILLEGAL_FLAG:
            erchar = mx_strndup(argument, 1);
            mx_printerr("illegal option, -- ");
            mx_printerr(erchar);
            mx_printerr("\n");
            mx_printerr("usage: ./uls [-");
            mx_printerr(MX_USED_FLAGS);
            mx_printerr("] [file ...]\n");
            free(erchar);
            break;
        default:
            break;
    }
}
