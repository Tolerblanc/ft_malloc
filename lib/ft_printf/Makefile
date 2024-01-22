CC = cc
CFLAGS = -Wall -Wextra
LIBC = ar rc
NAME = libftprintf.a
SRCS = ./ft_printf.c \
	./ft_printf_utils.c \
	./ft_printf_str.c \
	./ft_printf_parser.c \
	./ft_printf_integer.c \
	./ft_printf_hex.c \
	./ft_printf_cp.c \
	./ft_printf_addr.c 

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

$(NAME) : $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

bonus: $(NAME) $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME) $(bonus)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean all fclean re
