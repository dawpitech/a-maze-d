##
## EPITECH PROJECT, 2023
## A-Maze-D
## File description:
## Main Makefile of the project
##

CC	:=	gcc -std=gnu11

CFLAGS	=	-W
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wundef
CFLAGS	+=	-Wshadow
CFLAGS	+=	-Wunreachable-code
CFLAGS	+=	-Wmissing-prototypes
CFLAGS	+=	-Wno-unknown-pragmas
CFLAGS	+=	-pedantic -g3
CFLAGS	+=	-I./include/

T_CFLAGS	:= $(CFLAGS)
T_CFLAGS	+=	-lcriterion
T_CFLAGS	+=	--coverage

LIBS_FLAGS	=	-L./lib/ -lmy

BDIR	=	.build
T_BDIR	=	.buildTests

NAME	=	amazed
T_NAME	=	unit_tests

SRC = ./sources/a_maze_d.c

T_SRC	:=	$(SRC)

SRC	+=	./main.c

GCOVR_OUTPUT = gcovr

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
T_OBJ	=	$(T_SRC:%.c=$(T_BDIR)/%.o)

all:	$(NAME)

$(NAME):	build_lib $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBS_FLAGS)

$(T_NAME):	fclean build_lib $(T_OBJ)
	$(CC) $(T_OBJ) $(T_CFLAGS) -o $(T_NAME) $(LIBS_FLAGS)

$(T_BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(T_CFLAGS)

$(BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

asan:	CFLAGS += -fsanitize=address,leak,undefined -g3
asan: re

tests_run:	$(T_NAME)
	@ -./$(T_NAME)

tests_run_pp:	$(T_NAME)
	@ -./$(T_NAME) --verbose --full-stats --color=always -j8
	@ mkdir -p $(GCOVR_OUTPUT)
	@ gcovr --exclude=tests --html-details $(GCOVR_OUTPUT)/output.html

build_lib:
	@ make -C ./lib/my/

clean:
	@ rm -f $(T_OBJ)
	@ rm -f $(OBJ)
	@ rm -rf $(T_BDIR)
	@ rm -rf $(BDIR)
	@ rm -rf $(GCOVR_OUTPUT)

fclean:	clean
	@ rm -f $(NAME)
	@ rm -f $(T_NAME)
	@ rm -f $(SEGFAULT_NAME)
	@ rm -f $(FP_EXECP_NAME)
	@ make -C ./lib/my/ fclean

re:	fclean all

.PHONY : all asan tests_run_pp tests_run build_lib clean fclean re
