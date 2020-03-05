#include "uls.h"

void mx_print_name_list(t_list *files) {
    for (t_list *cur = files; cur; cur = cur->next) {
        t_file *temp = (t_file*)cur->data; 
        mx_printstr(temp->d_name);
        mx_printstr("\n");
    }
}

char which_file(t_file *file) {
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

    f_mode[0] = which_file(file);
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

void mx_user_group(t_file *file, t_flags *flags) {
    struct passwd *pw = getpwuid(file->stat.st_uid);
    struct group *group = getgrgid(file->stat.st_gid);

    mx_printchar(' ');
    if (flags->n == true) 
        mx_printint(pw->pw_uid);
    else
        mx_printstr(pw->pw_name);
    mx_printstr("  ");
    if (flags->n == true) 
        mx_printint(group->gr_gid);
    else
        mx_printstr(group->gr_name);
    mx_printchar(' ');
}

static void print_time(t_file *file) {
    char *time = ctime(&file->stat.st_mtimespec.tv_sec);

    for (int i = 4; time[i] != ' '; i++) // month
       mx_printchar(time[i]);
    mx_printchar(' ');
    for (int i = 8; i < 11; i++) // day
       mx_printchar(time[i]);
    for (int i = 11; i < 16; i++) // time
       mx_printchar(time[i]);
    mx_printchar(' '); 
}

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
            // mx_printint(temp->stat.st_size);
            mx_printstr(" ");
            print_time(temp);
            mx_printstr(temp->d_name);
            mx_printstr("\n");
        }
    }
}

void mx_output(t_flags *flags, t_list *files) {
    // mx_print_name_list(files);
    if (flags->l == true)
        mx_print_long_format(files, flags);
    else
        mx_print_name_list(files);
    // if (mx_strlen(file->d_dirent->d_name) > 0) {   //TODO: unprinted characters
        // if (flags->F || flags->p) {
        // if (temp_dirent->d_type == DT_DIR)
            // mx_printchar('/');
        // else if (flags->F && temp_dirent->d_type == DT_LNK)
            // mx_printchar('@');
        // else if (flags->F && temp_dirent->d_type == DT_SOCK)
            // mx_printchar('=');
        // else if (flags->F && temp_dirent->d_type == DT_FIFO)
            // mx_printchar('|');
        // else if (flags->F && temp_st && temp_st->st_mode & S_IXUSR)
            // mx_printchar('*');
        // }
    // }
// }
}
