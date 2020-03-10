#include "uls.h"

char mx_which_file(t_file *file) {
    if (MX_ISBLK(file->stat.st_mode) == true)
        return 'b';
    else if (MX_ISCHR(file->stat.st_mode) == true)
        return 'c';
    else if (MX_ISDIR(file->stat.st_mode) == true)
        return 'd';
    else if (MX_ISFIFO(file->stat.st_mode) == true)
        return 'p';
    else if (MX_ISLNK(file->stat.st_mode) == true)
        return 'l';
    else if (MX_ISSOCK(file->stat.st_mode) == true)
        return 's';
    else 
        return '-';
}

void mx_file_mode(t_file *file) {
    char f_mode[11];

    f_mode[0] = mx_which_file(file);
    f_mode[1] = (file->stat.st_mode & S_IRUSR) ? 'r' : '-';
    f_mode[2] = (file->stat.st_mode & S_IWUSR) ? 'w' : '-';
    f_mode[3] = (file->stat.st_mode & S_IXUSR) ? 'x' : '-';
    f_mode[4] = (file->stat.st_mode & S_IRGRP) ? 'r' : '-';
    f_mode[5] = (file->stat.st_mode & S_IWGRP) ? 'w' : '-';
    f_mode[6] = (file->stat.st_mode & S_IXGRP) ? 'x' : '-';
    f_mode[7] = (file->stat.st_mode & S_IROTH) ? 'r' : '-';
    f_mode[8] = (file->stat.st_mode & S_IWOTH) ? 'w' : '-';
    f_mode[9] = (file->stat.st_mode & S_IXOTH) ? 'x' : '-';
    f_mode[10] = '\0';
    mx_printstr(&f_mode[0]);
    mx_printstr(" ");
}

void mx_print_name_with_tabl(long len, char *name) {
    for (int i = 0; name[i] != '\0'; i++, len--)
        mx_printchar(name[i]);
    while (len-- > 0)
        mx_printchar(' ');
}

void mx_user_group(t_file *file, t_daddy *daddy) {
    struct passwd *pw = getpwuid(file->stat.st_uid);
    struct group *group = getgrgid(file->stat.st_gid);

    if (pw == NULL)
        printf("%s\n", strerror(errno));
    mx_printchar(' ');
    if (pw == NULL) 
        mx_print_with_tabl(file->stat.st_uid, daddy->own_name, true);
    else
        mx_print_name_with_tabl(daddy->own_name, pw->pw_name);
    mx_printstr("  ");
    if (group == NULL) 
        mx_print_with_tabl(file->stat.st_gid, daddy->grp_name, true);
    else
        mx_print_name_with_tabl(daddy->grp_name, group->gr_name);
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
    
    for (int i = 4; time[i] != ' '; i++) // month
        mx_printchar(time[i]);
    mx_printchar(' ');
    for (int i = 8; i < 11; i++) // day
        mx_printchar(time[i]);
    if ((curr_time - 15778463) > *file_time || curr_time < *file_time) {
        mx_printchar(' ');
        for(int i = 20; i < 24; ++i)
            mx_printchar(time[i]);  //year
    }
    else {
        for (int i = 11; i < 16; i++) // time
            mx_printchar(time[i]);
    }
    mx_printchar(' ');
}
