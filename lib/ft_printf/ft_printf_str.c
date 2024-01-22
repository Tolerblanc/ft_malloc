/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:48:17 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 14:01:11 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_strlen(const char *str, t_opts *opt)
{
	int		ret;

	if (opt->precision == 0 && opt->dot == 1)
		return (0);
	ret = 0;
	while (str[ret] != '\0')
		ret++;
	return (ret);
}

int	print_str(va_list ap, t_opts *opt)
{
	int		len;
	int		ret;
	char	*s;

	ret = 0;
	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	len = ft_printf_strlen((const char *)s, opt);
	if (opt->flag == -1)
		ret += print_space_s(opt, len);
	ret += print_zero_s(opt, len);
	ret += ft_putstr(s, opt);
	if (opt->flag == 1)
		ret += print_space_s(opt, len);
	return (ret);
}

int	print_space_s(t_opts *opt, int len)
{
	int		i;

	i = 0;
	if (opt->precision && opt->precision < len)
	{
		while (i < opt->width - opt->precision)
		{
			i++;
			ft_putchar(' ');
		}
	}
	else if (opt->flag != 0)
	{
		while (i < opt->width - len)
		{
			i++;
			ft_putchar(' ');
		}
	}
	return (i);
}

int	print_zero_s(t_opts *opt, int len)
{
	int		i;

	i = 0;
	if (opt->flag == 0)
	{
		while (i++ < opt->width - len)
		{
			i++;
			ft_putchar('0');
		}
	}
	return (i);
}

int	ft_putstr(const char *s, t_opts *opt)
{
	int		i;

	i = 0;
	if (opt->precision == 0 && opt->dot == 1 && opt->type != 7)
		return (i);
	else if (opt->precision)
	{
		while (i < opt->precision && s[i] != '\0')
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	else
	{
		while (s[i] != '\0')
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	return (i);
}
