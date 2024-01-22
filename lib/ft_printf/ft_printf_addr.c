/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 02:18:23 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 13:56:20 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_addrlen(unsigned long ad, t_opts *opt)
{
	int				len;
	unsigned long	tmp;

	len = 0;
	tmp = ad;
	while (tmp >= 1)
	{
		tmp /= 16;
		len++;
	}
	opt->width -= 2;
	if (opt->dot == 1 && opt->precision == 0 && ad == 0)
		return (0);
	if (!ad)
		return (1);
	return (len);
}

int	print_address(va_list ap, t_opts *opt)
{
	int				len;
	int				ret;
	unsigned long	add;

	ret = 0;
	add = va_arg(ap, unsigned long);
	len = ft_addrlen(add, opt);
	if (opt->flag != 1)
		ret += print_space_p(opt, len);
	ret += ft_putstr("0x", opt);
	ret += print_zero_p(opt, len);
	ft_putnbr_base(add, opt, &ret);
	if (opt->flag == 1)
		ret += print_space_p(opt, len);
	return (ret);
}

int	print_space_p(t_opts *opt, int len)
{
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	if (len < opt->precision)
	{
		while (i++ < opt->width - opt->precision)
		{
			ft_putchar(' ');
			ret++;
		}
	}
	else if (!(opt->precision == 0 && opt->flag == 0 && opt->dot == 0))
	{
		while (i++ < opt->width - len)
		{
			ft_putchar(' ');
			ret++;
		}
	}
	return (ret);
}

int	print_zero_p(t_opts *opt, int len)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (len < opt->precision)
	{
		while (i++ < opt->precision - len)
		{
			ft_putchar('0');
			ret++;
		}
	}
	else if (opt->precision == 0 && opt->flag == 0 && opt->dot == 0)
	{
		while (i++ < opt->width - len)
		{
			ft_putchar('0');
			ret++;
		}
	}
	return (ret);
}
