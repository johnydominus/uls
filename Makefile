NAME = uls

SRCD = src
INCD = inc
OBJD = obj
LBMXD = libmx
LIBMX = libmx

LBMX = libmx.a
INC = uls.h
SRC  = 	free_functions.c \
		long_format.c \
		main.c \
		mx_check_flag_validity.c \
		mx_check_flags.c \
		mx_comparators_one.c \
		mx_comparators_two.c \
		mx_error.c \
		mx_flag_parser.c \
		mx_init_flags.c \
		mx_m_output.c \
		mx_multicol.c \
		mx_multicol_output.c \
		mx_output.c \
		mx_print_filename.c \
		mx_print_long_format.c \
		mx_process_dir.c \
		mx_process_list.c \
		mx_save_args.c \
		mx_sort_files.c \
		mx_sort_lists.c \
		long_format_2.c \
		long_format_3.c \

INCLUDE = -I $(LBMXD)/$(INCD) \
	-I $(INCD) \

LBMXS = $(addprefix $(LBMXD)/, $(LBMX))
INCS = $(addprefix $(INCD)/, $(INC))
SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))
	
CFLAGS = -std=c11 -g $(addprefix -W, all extra error pedantic)
CC = clang

all: $(NAME)

install: $(NAME) clean

$(LBMXS):
	@make -sC $(LBMXD)

$(LIBMX): $(LBMXS)
	@make -sC $(LBMXD)
	
$(NAME): $(OBJS) $(LIBMX)
	@$(CC) $(CFLAGS) $(LBMXS) $(OBJS) -o $@
	@printf "\x1b[32;1m$@ created\x1b[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@printf "\x1b[32mcompiled: \x1b[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

uninstall: clean
	@make -sC $(LBMXD) $@
	@rm -rf $(NAME)
	@printf "\x1b[34;1mdeleted $(NAME)\x1b[0m\n"

clean:
	@make -sC $(LBMXD) $@
	@rm -rf $(OBJD)
	@printf "\x1b[34;1mdeleted $(OBJD)\x1b[0m\n"

reinstall: uninstall install
