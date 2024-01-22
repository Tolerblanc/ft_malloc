/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:17:17 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 13:58:27 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intlen(long long n, t_opts *opt)
{
	int					i;
	unsigned long long	tmp;

	if (opt->dot == 1 && opt->precision == 0 && n == 0)
		return (0);
	i = 0;
	if (n > 0)
		tmp = n;
	else
		tmp = n * (-1);
	while (tmp >= 1)
	{
		tmp /= 10;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}

int	print_int(va_list ap, t_opts *opt)
{
	int					len;
	int					ret;
	long long			n;

	n = 0;
	ret = 0;
	if (opt->type <= 1)
		n = va_arg(ap, int);
	else if (opt->type == 2)
		n = va_arg(ap, unsigned int);
	len = ft_intlen(n, opt);
	if (opt->flag != 1)
		ret += print_space_i(opt, len, n);
	if (n < 0)
	{
		ft_putchar('-');
		ret++;
	}
	ret += print_zero_i(opt, len, n);
	ft_putnbr(n, opt, &ret);
	if (opt->flag == 1)
		ret += print_space_i(opt, len, n);
	return (ret);
}

int	print_space_i(t_opts *opt, int len, long long n)
{
	int					i;
	int					ret;

	ret = 0;
	if (opt->type != 2 && n < 0)
		i = 1;
	else
		i = 0;
	if (len < opt->precision)
	{
		while (i++ < (opt->width - opt->precision))
		{
			ft_putchar(' ');
			ret++;
		}
	}
	else if (!(opt->precision == 0 && opt->flag == 0 && opt->dot == 0))
	{
		while (i++ < (opt->width - len))
		{
			ft_putchar(' ');
			ret++;
		}
	}
	return (ret);
}

int	print_zero_i(t_opts *opt, int len, long long n)
{
	int					i;
	int					ret;

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
		if (opt->type != 2 && n < 0)
			i = 1;
		while (i++ < opt->width - len)
		{
			ft_putchar('0');
			ret++;
		}
	}
	return (ret);
}

void	ft_putnbr(long long nbr, t_opts *opt, int *ret)
{
	if (nbr == 0 && !(opt->dot == 1 && opt->precision == 0))
	{
		ft_putchar('0');
		(*ret)++;
	}
	else if (nbr == -2147483648)
	{
		ft_putnbr(-214748364, opt, ret);
		ft_putchar('8');
		(*ret)++;
	}
	else if (nbr < 0)
		ft_putnbr(-nbr, opt, ret);
	else if (nbr > 0)
	{
		if (nbr >= 10)
			ft_putnbr(nbr / 10, opt, ret);
		ft_putchar(nbr % 10 + '0');
		(*ret)++;
	}
}
