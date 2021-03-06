# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/26 12:26:28 by fpetras           #+#    #+#              #
#    Updated: 2019/04/01 16:44:07 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC = main.c \
	  usage.c \
	  command.c \
	  options.c \
	  options_hash.c \
	  read.c \
	  join.c \
	  print.c \
	  hash.c \
	  md5.c \
	  md5_algo.c \
	  sha224_256.c \
	  sha224_256_algo.c \
	  sha384_512.c \
	  sha384_512_algo.c \
	  hash_value.c \
	  rotate.c \
	  endianness.c

OBJPATH = obj/
OBJ = $(addprefix $(OBJPATH),$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

# ----- ANSI Escape Sequences ----- #
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
UNDERLINE = \033[0;4m
TEXT_RESET = \033[0;0m
# --------------------------------- #

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(TEXT_RESET)"
	@echo "$(UNDERLINE)libft:$(TEXT_RESET)"
	@echo "$(BLUE)"
	@make -C libft
	@echo "$(TEXT_RESET)"
	@echo "Generating executable file:\n$(WHITE)$@\n$(TEXT_RESET)"
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) libft/libft.a
	@echo "$(GREEN)Success$(TEXT_RESET)"

$(OBJPATH)%.o: %.c
	@test -d $(OBJPATH) || mkdir $(OBJPATH)
	@echo "$(CYAN)Compiling $< $(TEXT_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	@./test.sh all

test_md5: $(NAME)
	@./test.sh md5

test_sha: $(NAME)
	@./test.sh sha224 sha256 sha384 sha512 sha512224 sha512256

test_sha224: $(NAME)
	@./test.sh sha224

test_sha256: $(NAME)
	@./test.sh sha256

test_sha384: $(NAME)
	@./test.sh sha384

test_sha512: $(NAME)
	@./test.sh sha512

test_sha512224: $(NAME)
	@./test.sh sha512224

test_sha512256: $(NAME)
	@./test.sh sha512256

clean:
	@make clean -C libft
	@rm -rf $(OBJPATH)
	@rm -rf $(NAME).dSYM
	@rm -f file file1 file2

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test test_md5 test_sha224 test_sha256 test_sha384 test_sha512 test_sha512224 test_sha512256
