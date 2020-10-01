# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 13:07:44 by widraugr          #+#    #+#              #
#    Updated: 2020/10/01 09:34:55 by mixfon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

LIBDIR = ./libft

FILE_C = check_arguments.c\
		 new_elem.c\
		 press_delete.c\
		 press_space.c\
		 print_elem_or_error_size.c\
		 working_signals.c

FLAGS = -Wall -Wextra -Werror -I libft -I include 

FLIB = -L ./libft -lftprintf 

DIRC = ./source/

VPATH = $(DIROBJ)

DIROBJ = ./obj/

OBJ = $(addprefix $(DIROBJ), $(FILE_C:.c=.o))

all : $(NAME)

$(NAME): $(DIROBJ) $(OBJ) 
	make -C $(LIBDIR)
	gcc $(FLAGS) $(OBJ) $(FLIB) $(FMLXLIB) -ltermcap -o $(NAME)

$(DIROBJ)%.o : $(DIRC)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ):
	mkdir -p $(DIROBJ)

clean:
	/bin/rm -rf $(DIROBJ)
	
fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -rf *.dSYM
	make fclean -C $(LIBDIR)
	
re: fclean all 
