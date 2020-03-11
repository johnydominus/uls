#include "uls.h"

static void print_name_with_tabl(long len, char *name) {
    for (int i = 0; name[i] != '\0'; i++, len--)
        mx_printchar(name[i]);
    while (len-- > 0)
        mx_printchar(' ');
}

void mx_user_group(t_file *file, t_daddy *daddy) {
    struct passwd *pw = getpwuid(file->stat.st_uid);
    struct group *group = getgrgid(file->stat.st_gid);

    mx_printchar(' ');
    if (pw == NULL) 
        mx_print_with_tabl(file->stat.st_uid, daddy->own_name, true);
    else
        print_name_with_tabl(daddy->own_name, pw->pw_name);
    mx_printstr("  ");
    if (group == NULL)
        mx_print_with_tabl(file->stat.st_gid, daddy->grp_name, true);
    else
        print_name_with_tabl(daddy->grp_name, group->gr_name);
    mx_printchar(' ');
}

static time_t *set_time(t_file *file, t_flags *flags) {
    time_t *temp_time;

    if (flags->c)
        temp_time = &(file->stat.st_ctimespec.tv_sec);
    else if (flags->u)
        temp_time = &(file->stat.st_atimespec.tv_sec);
    else if (flags->U)
        temp_time = &(file->stat.st_birthtimespec.tv_sec);
    else
        temp_time = &(file->stat.st_mtimespec.tv_sec);
    return temp_time;
}

void mx_print_time(t_file *file, t_flags *flags) {
    time_t *file_time = set_time(file, flags);
    time_t curr_time = time(NULL);
    char *time = ctime(file_time);

    for (int i = 4; time[i] != ' '; i++)    // month
        mx_printchar(time[i]);
    mx_printchar(' ');
    for (int i = 8; i < 11; i++)            // day
        mx_printchar(time[i]);
    if ((curr_time - 15768000) > *file_time || curr_time < *file_time) {
        mx_printchar(' ');
        for(int i = 20; i < 24; ++i)
            mx_printchar(time[i]);          //year
    }
    else {
        for (int i = 11; i < 16; i++)       // time
            mx_printchar(time[i]);
    }
    mx_printchar(' ');
}
