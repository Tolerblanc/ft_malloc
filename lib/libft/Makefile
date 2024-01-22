# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 00:11:46 by hyunjuki          #+#    #+#              #
#    Updated: 2023/01/18 12:40:30 by hyunjuki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I .
LIBC = ar rc
NAME = libft.a
SRCS = ./ft_atoi.c \
	./ft_bzero.c \
	./ft_calloc.c \
	./ft_isalnum.c \
	./ft_isalpha.c \
	./ft_isascii.c \
	./ft_isdigit.c \
	./ft_isprint.c \
	./ft_isspace.c \
	./ft_itoa.c \
	./ft_memccpy.c \
	./ft_memchr.c \
	./ft_memcmp.c \
	./ft_memcpy.c \
	./ft_memmove.c \
	./ft_memset.c \
	./ft_putchar_fd.c \
	./ft_putendl_fd.c \
	./ft_putnbr_fd.c \
	./ft_putstr_fd.c \
	./ft_split.c \
	./ft_strchr.c \
	./ft_strdup.c \
	./ft_strjoin.c \
	./ft_strlcat.c \
	./ft_strlcpy.c \
	./ft_strlen.c \
	./ft_strmapi.c \
	./ft_strncmp.c \
	./ft_strnstr.c \
	./ft_strrchr.c \
	./ft_strtrim.c \
	./ft_substr.c \
	./ft_tolower.c \
	./ft_toupper.c \
	./get_next_line.c\

BONUS_SRCS = ./ft_lstadd_back.c \
	./ft_lstadd_front.c \
	./ft_lstclear.c \
	./ft_lstdelone.c \
	./ft_lstiter.c \
	./ft_lstlast.c \
	./ft_lstmap.c \
	./ft_lstnew.c \
	./ft_lstsize.c \

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all : $(NAME)

bonus : $(NAME) $(BONUS_OBJS)
	$(LIBC) $(NAME) $(BONUS_OBJS)

clean :
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME) $(bonus)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : bonus clean fclean re