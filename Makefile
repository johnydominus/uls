NAME = uls
INC = ./inc/
INCLIB = ./libmx/inc/
HEADTMP = ./uls.h ./libmx.h

SRC = main.c \
	  mx_process_list.c \
	  mx_check_flag_validity.c \
	  mx_error.c \
	  mx_flag_parser.c \
	  mx_init_flags.c \
	  mx_output.c \
	  mx_save_args.c \
	  mx_process_dir.c \
	  mx_sort_files.c \
	  mx_check_flags.c \
	  free_functions.c \
	  mx_comparators_one.c \
	  mx_comparators_two.c \
	  mx_sort_lists.c \
	  mx_print_filename.c \
	  mx_multicol_output.c \
	  mx_multicol.c \
	  mx_m_output.c

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

OBJO = $(addprefix obj/, $(OBJ))

# CFLGS = -std=c11 -Wall -Wpedantic -Werror -Wextra -g -fsanitize=address
# CFLGS = -std=c11 -Wall -Wpedantic -Wextra -g -fsanitize=address # Warnig does not error 
  CFLGS = -std=c11 -Wall -Wpedantic -Wextra -g -fsanitize=address -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable #Withou "unused" warning;
# CFLGS = -std=c11 -Wall -Wpedantic -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable #Withou "unused" warning; To use leaks command;

all: install clean

install:
#	@make -C libmx install
	@clang $(CFLGS) -I $(INC) -I $(INCLIB) -c $(SRCS)
	@mkdir -p obj
	@mv $(OBJ) ./obj
	@clang $(CFLGS) $(OBJO) libmx/libmx.a -o $(NAME)

clean:
#	@make -C libmx/ -f Makefile clean
	@rm -rf ./obj
	@rm -rf libmx.a
	@rm -rf ./libmx/obj

uninstall: clean
#	@make -C libmx/ -f Makefile uninstall
	@rm -rf $(NAME)

reinstall: uninstall all
