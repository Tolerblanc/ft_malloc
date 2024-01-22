/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:48:20 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 13:56:34 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int print_char(va_list ap, t_opts *opt)
{
	int		tmp;
	int		len;

	len = 0;
	if (opt->flag == -1)
		len += print_space_c(opt);
	len += print_zero_c(opt);
	if (opt->type == 8)
		ft_putchar('%');
	else
	{
		tmp = va_arg(ap, int);
		ft_putchar(tmp);
	}
	len++;
	if (opt->flag == 1)
		len += print_space_c(opt);
	return (len);
}

int	print_zero_c(t_opts *opt)
{
	int		i;

	i = 0;
	if (opt->flag == 0)
	{
		while (i < opt->width - 1)
		{
			i++;
			ft_putchar('0');
		}
	}
	return (i);
}

int	print_space_c(t_opts *opt)
{
	int		i;

	i = 0;
	while (i < opt->width - 1)
	{
		i++;
		ft_putchar(' ');
	}
	return (i);
}
