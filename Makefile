# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/18 20:52:10 by rfrey             #+#    #+#              #
#    Updated: 2014/05/03 18:20:45 by rfrey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_script
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
PATH_OBJ = obj
PATH_SRC = src
PATH_INC = inc
PATH_LIBFT = libft
LIBFT = libft.a
PATH_LIBFT_INC = $(PATH_LIBFT)/includes

SRC = main.c script.c script2.c get_pty.c get_env.c term.c buffer.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all : $(NAME)

$(NAME) : $(OBJ) $(PATH_LIBFT)/$(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo " done !"

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@echo -n .
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(PATH_INC)/ -I $(PATH_LIBFT_INC)/

$(PATH_LIBFT)/$(LIBFT) : $(PATH_LIBFT)/Makefile
	@cd $(PATH_LIBFT)/ && $(MAKE)

clean :
	@rm -f $(OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) $@

fclean : clean
	@rm -f $(NAME)
	@rm -f $(PATH_LIBFT)/$(LIBFT)

re : fclean all

.PHONY: clean fclean
