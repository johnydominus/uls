#include "uls.h"

long mx_strlen_own(t_file *file) {
    struct passwd *pw = getpwuid(file->stat.st_uid);
    long result = 0;

    if (pw == NULL) {
        for (uid_t uid = file->stat.st_uid; uid > 0; uid /= 10)
            result *= 10;
    }
    else
        return strlen(pw->pw_name);
    return result; 
}

long mx_strlen_grp(t_file *file) {
    struct group *group = getgrgid(file->stat.st_gid);
    long result = 1;

    if (group == NULL) {
        for (gid_t gid = file->stat.st_gid; gid > 0; gid /= 10)
            result *= 10;
    }
    else
        return mx_strlen(group->gr_name);
    return result;        
}

void mx_print_with_tabl(long num, long num_of_dig, bool name) {

    char *result = mx_itoa(num);
    // if (num == 0)
        // num_of_dig /= 10;
    if (name == true) {
        mx_printstr(result);
        for (num_of_dig = num_of_dig - mx_strlen(result); num_of_dig > 0;
             num_of_dig--)
            mx_printchar(' ');
    }
    else {
        for (num_of_dig = num_of_dig - mx_strlen(result); num_of_dig > 0;
             num_of_dig--)
            mx_printchar(' ');
        mx_printstr(result);
    }
}

void daddy_love_auditor(t_daddy *daddy) {
    int num_of_dig = 1;

    for (int largest = daddy->size; largest > 0; largest /= 10)
        num_of_dig++;
    daddy->size = num_of_dig;
    num_of_dig = 1;
    for (int largest = daddy->n_link; largest > 0; largest /= 10)
        num_of_dig++;
    daddy->n_link = num_of_dig;
    if (daddy->ma_size != 0) {
        daddy->ma_size += 2;
        if (daddy->size > 8)
            daddy->ma_size += daddy->size - 8;
        else
            daddy->size = 9;
    }
}

void mx_set_daddy(t_daddy *daddy) {
    daddy->n_link = 0;
    daddy->own_name = 0;
    daddy->grp_name = 0;
    daddy->size = 0;
    daddy->ma_size = 0;
    daddy->total = 0;
}

void mx_fuck_auditor(t_file *file, t_daddy *daddy) {
    long major = ((int)(((unsigned int)file->stat.st_rdev >> 24) & 0xff)); 
    long size = 0;

    for (; major > 0; major /= 10) {
       size++; 
    } 
    if (daddy->ma_size < size)
        daddy->ma_size = size;
}

t_daddy who_the_daddy(t_list *files) {
    t_daddy daddy;

    mx_set_daddy(&daddy);
    for (t_list *cur = files; cur; cur = cur->next) {
        daddy.total += ((t_file*)cur->data)->stat.st_blocks;
        if (((t_file*)cur->data)->stat.st_size > daddy.size)
            daddy.size = ((t_file*)cur->data)->stat.st_size;
        if (mx_which_file((t_file*)cur->data) == 'b' ||
            mx_which_file((t_file*)cur->data) == 'c')
            mx_fuck_auditor(((t_file*)cur->data), &daddy);
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

void mx_print_major_minor(t_file *file, long ma_size) {
    long major = ((int)(((unsigned int)file->stat.st_rdev >> 24) & 0xff)); 
    long minor = ((int)((unsigned int)(file->stat.st_rdev) & 0xffffff));
    int size_of_minor = 1;
    char *hex = NULL;

    mx_print_with_tabl(major, ma_size, false);
    mx_printchar(',');
    if (minor < 256) {
        if (minor != 0)
            for (int largest = minor; largest > 0; largest /= 10)
                size_of_minor++;
        else
            size_of_minor++;
        for (; size_of_minor < 5; size_of_minor++)
            mx_printchar(' ');
       mx_printint(minor); 
    }
    else {
        hex = mx_nbr_to_hex(minor);
        mx_printstr(" 0x");
        for (int i = mx_strlen(hex); i < 8; i++)
            mx_printchar('0');
        mx_printstr(mx_nbr_to_hex(minor));
    }
}

static void print_link(t_file *file) {
    if (MX_ISLNK(file->stat.st_mode)) {
        char *buf = NULL;
        ssize_t size = (file->stat.st_size < 100) ? 100 : file->stat.st_size;
        char *name = (file->full_path != NULL) ?
        file->full_path : file->d_name;

        
        buf = mx_strnew(size + 1);
        size = readlink(name, buf, size + 1);
        if (size > 0) {
            mx_printstr(" -> ");
            mx_printstr(buf);
        }
        if (buf != NULL)
            free(buf);
    }
}

void mx_print_long_format(t_list *files, t_flags *flags) {
    if (flags->l == true) {
        t_daddy daddy = who_the_daddy(files);
        // printf("daddy = %ld, %ld; group = %ld own = %ld", daddy.size, daddy.n_link, daddy.own_name, daddy.grp_name);

        if (files != NULL) {
            mx_printstr("total ");
            mx_printint(daddy.total);
            mx_printchar('\n');
        }
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
            mx_printstr(temp->d_name);
            print_link(temp);
            mx_printstr("\n");
        }
    }
}
