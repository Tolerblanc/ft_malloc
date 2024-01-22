/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:11:15 by hyunjuki          #+#    #+#             */
/*   Updated: 2021/03/03 14:11:03 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# define MAND "diucsxXp%"
# define DEC "diu"
# define DIGIT "0123456789"
# define SHEXC "0123456789abcdef"
# define LHEXC "0123456789ABCDEF"

typedef struct	s_options
{
	int			flag;
	int			width;
	int			precision;
	int			type;
	int			dot;
}				t_opts;

int				ft_printf(const char *format, ...);
int				parse_string(const char *str, va_list ap, int *idx);
int				print_args(va_list ap, t_opts *opt);

void			init_struct(t_opts *opt);
int				fill_struct(const char *s, va_list ap, t_opts *o, int *i);
void			parse_flag(const char *s, t_opts *o, int *i);
void			parse_prec(const char *s, va_list ap, t_opts *o, int *i);
void			parse_width(const char *s, va_list ap, t_opts *o, int *i);

int				print_hex(va_list ap, t_opts *opt);
int				ft_hexlen(unsigned int hx, t_opts *opt);
void			ft_putnbr_base(long long nbr, t_opts *opt, int *ret);

int				print_address(va_list ap, t_opts *opt);
int				ft_addrlen(unsigned long ad, t_opts *opt);
int				print_space_p(t_opts *opt, int len);
int				print_zero_p(t_opts *opt, int len);

int				print_int(va_list ap, t_opts *opt);
int				ft_intlen(long long n, t_opts *opt);
int				print_space_i(t_opts *opt, int len, long long n);
int				print_zero_i(t_opts *opt, int len, long long n);
void			ft_putnbr(long long nbr, t_opts *opt, int *ret);

int				print_char(va_list ap, t_opts *opt);
int				print_zero_c(t_opts *opt);
int				print_space_c(t_opts *opt);

int				print_str(va_list ap, t_opts *opt);
int				ft_printf_strlen(const char *str, t_opts *opt);
int				print_space_s(t_opts *opt, int len);
int				print_zero_s(t_opts *opt, int len);
int				ft_putstr(const char *s, t_opts *opt);

int				ft_printf_atoi(const char *str, int *i);
int				ft_printf_strchr(const char *s, int c);
int				ft_isspace(const char c);
int				ft_isdigit(int c);
void			ft_putchar(char c);

#endif
