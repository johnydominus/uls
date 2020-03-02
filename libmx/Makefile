NAME = libmx.a

INC = ./inc/libmx.h
HEADTMP = ./libmx.h
OBJH = obj/libmx.h

SRC = ./mx_atoi.c \
	  ./mx_strdup_delim.c \
	  ./mx_isdigit.c \
	  ./mx_isalpha.c \
	  ./mx_printerr.c \
	  ./mx_sort_list.c \
	  ./mx_list_size.c \
	  ./mx_pop_back.c \
	  ./mx_pop_front.c \
	  ./mx_push_front.c \
	  ./mx_push_back.c \
	  ./mx_create_node.c \
	  ./mx_memmove.c \
	  ./mx_memcmp.c \
	  ./mx_memccpy.c \
	  ./mx_memcpy.c \
	  ./mx_memset.c \
	  ./mx_replace_substr.c \
	  ./mx_del_extra_spaces.c \
	  ./mx_read_line.c \
	  ./mx_file_to_str.c \
	  ./mx_strjoin.c \
	  ./mx_strtrim.c \
	  ./mx_strnew.c \
	  ./mx_count_words.c \
	  ./mx_count_substr.c \
	  ./mx_get_substr_index.c \
	  ./mx_strstr.c \
	  ./mx_strcat.c \
	  ./mx_strncpy.c \
	  ./mx_strcpy.c \
	  ./mx_strndup.c \
	  ./mx_strdup.c \
	  ./mx_get_char_index.c \
	  ./mx_strdel.c \
	  ./mx_str_reverse.c \
	  ./mx_swap_char.c \
	  ./mx_strlen.c \
	  ./mx_quicksort.c \
	  ./mx_bubble_sort.c \
	  ./mx_foreach.c \
	  ./mx_itoa.c \
	  ./mx_hex_to_nbr.c \
	  ./mx_nbr_to_hex.c \
	  ./mx_sqrt.c \
	  ./mx_pow.c \
	  ./mx_print_strarr.c \
	  ./mx_printstr.c \
	  ./mx_print_unicode.c \
	  ./mx_printchar.c \
	  ./mx_binary_search.c \
	  ./mx_abs.c \
	  ./mx_memchr.c \
	  ./mx_memrchr.c \
	  ./mx_memmem.c \
	  ./mx_realloc.c \
	  ./mx_del_strarr.c \
	  ./mx_isspace.c \
	  ./mx_printint.c \
	  ./mx_strcmp.c \
	  ./mx_strlen_delim.c \
	  ./mx_strncmp.c \
	  ./mx_strsplit.c \
	  ./mx_strtrim_delim.c \
	  ./mx_merge_sort.c

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

OBJO = $(addprefix obj/, $(OBJ))

CFLGS = -g -c -std=c11 -Wall -Wextra -Wpedantic -Werror 

all: install clean

install:
	@cp $(SRCS) $(INC) .
	@clang $(CFLAGS) -c $(SRC) $(INC)
	@ar -rc $(NAME) $(OBJ)
	@mkdir -p obj
	@mv $(OBJ) obj

uninstall: clean
	@rm -rf $(NAME)
	@rm -rf obj
	@rm -rf a.out
	@rm -rf inc/libmx.h.gch

clean:
	@rm -rf $(OBJ) $(SRC) $(HEADTMP)

reinstall: uninstall install