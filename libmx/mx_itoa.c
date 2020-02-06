#include "libmx.h"

static void check_minus(int *minus, int *number, int *len);
static void define_len(int *temp, int *len);
static void save_num(int *number, char *num, int *i);
static void add_minus(int *minus, char *num, int *i);

char *mx_itoa(int number) {
    int len = 1;
    int minus = 0;
    int i = 0;
    int temp;
    char *num = NULL;

    if (number == -2147483648)
        num = "-2147483648";
    else if (number == 0)
        num = "0";
    else {
        check_minus(&minus, &number, &len);
        temp = number;
        define_len(&temp, &len);
        num = mx_strnew(len);
        save_num(&number, num, &i);
        add_minus(&minus, num, &i);
        mx_str_reverse(num);
    }
    return num;
}

static void check_minus(int *minus, int *number, int *len) {
    if ((*minus = *number) < 0) { 
        (*len)++;
        *number = -(*number);
    }
}

static void define_len(int *temp, int *len) {
    while ((*temp / 10) > 0) {
        (*len)++;
        *temp /= 10;
    }
}

static void save_num(int *number, char *num, int *i) {
    while (*number != 0) {
        num[(*i)++] = *number % 10 + '0';
        *number /= 10;
    }    
}

static void add_minus(int *minus, char *num, int *i) {
        if (*minus < 0)
            num[(*i)++] = '-';
}
