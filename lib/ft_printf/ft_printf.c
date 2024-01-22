/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:41:17 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 14:02:22 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_string(const char *str, va_list ap, int *idx)
{
	int		len;
	t_opts	*opt;

	if (str[*idx] == '%')
	{
		if (!(opt = malloc(sizeof(t_opts))))
			return (-1);
		init_struct(opt);
		if ((len = fill_struct(str, ap, opt, idx)) == -1)
			return (-1);
		if ((len = print_args(ap, opt)) == -1)
			return (-1);
		free(opt);
		return (len);
	}
	else
	{
		ft_putchar(str[(*idx)++]);
		return (1);
	}
}

int	print_args(va_list ap, t_opts *opt)
{
	int		ret;

	ret = 0;
	if (opt->type == -1)
		return (-1);
	else if (opt->type == 0 || opt->type == 1 || opt->type == 2)
		ret = print_int(ap, opt);
	else if (opt->type == 5 || opt->type == 6)
		ret = print_hex(ap, opt);
	else if (opt->type == 7)
		ret = print_address(ap, opt);
	else if (opt->type == 3 || opt->type == 8)
		ret = print_char(ap, opt);
	else if (opt->type == 4)
		ret = print_str(ap, opt);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		idx;
	int		len;
	int		temp;
	va_list	ap;

	len = 0;
	idx = 0;
	va_start(ap, format);
	while (format[idx] != '\0')
	{
		temp = parse_string(format, ap, &idx);
		if (temp == -1)
			return (-1);
		else
			len += temp;
	}
	va_end(ap);
	if (len < 0 || len == INT_MAX)
		return (-1);
	return (len);
}
