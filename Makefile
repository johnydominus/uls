NAME = uls
INC = ./inc/uls.h
INCLIB = ./libmx/inc/libmx.h
HEADTMP = ./uls.h ./libmx.h

SRC = ./main.c

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

OBJO = $(addprefix obj/, $(OBJ))

CFLGS = -std=c11 -Wall -Wpedantic -Werror -Wextra

all: install clean

install:
	@make -C libmx install
	@cp $(INC) $(INCLIB) $(SRCS) .
	@clang $(CFLGS) -c $(SRC)
	@mkdir obj
	@mv $(OBJ) ./obj
	@clang $(CFLGS) $(OBJO) libmx/libmx.a -o $(NAME)

clean:
	@make -C libmx/ -f Makefile clean
	@rm -rf $(OBJ) $(OBJO) $(SRC) $(HEADTMP)
	@rm -rf ./obj
	@rm -rf libmx.a
	@rm -rf ./libmx/obj

uninstall: clean
	@make -C libmx/ -f Makefile uninstall
	@rm -rf $(NAME)

reinstall: uninstall all
