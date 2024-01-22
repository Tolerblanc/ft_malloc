NAME = libft_malloc_$(HOSTTYPE).so

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
LIBC = ar rc

LIB_PATH = ./lib
LIBFT_PATH = $(LIB_PATH)/libft
LIBFT_PRINTF_PATH = $(LIB_PATH)/ft_printf

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRCS_NAME = main.c

SRCS_PATH = ./srcs
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS_PATH = ./objs
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

INCS = -I./include
LIBINCS = -L$(LIBFT_PATH) -lft -L$(LIBFT_PRINTF_PATH) -lftprintf

all: $(NAME)

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c
	@echo building obj files : $<
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

$(NAME): $(OBJS)
	@echo building libft.a
	@$(MAKE) --silent -C $(LIBFT_PATH)
	@echo building libftprintf.a
	@$(MAKE) --silent -C $(LIBFT_PRINTF_PATH)
	@echo building $(NAME)
	@$(CC) $(CFLAGS) -shared -o $@ $^ $(LIBINCS)
	@echo making symbolic link
	@ln -sf $(NAME) libft_malloc.so

clean:
	@echo delete object files
	@rm -f $(OBJS)
	@$(MAKE) --silent -C $(LIBFT_PATH) clean
	@$(MAKE) --silent -C $(LIBFT_PRINTF_PATH) clean

fclean: clean
	@rm -rf libft_malloc*.so
	@rm -f test
	@$(MAKE) --silent -C $(LIBFT_PATH) fclean
	@$(MAKE) --silent -C $(LIBFT_PRINTF_PATH) fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

test: $(NAME)
    @export DYLD_LIBRARY_PATH=$(PWD):$$DYLD_LIBRARY_PATH; \
    $(CC) $(CFLAGS) -o test test.c -L. -lft_malloc -I./include; \
    ./test

.PHONY: all clean fclean re test