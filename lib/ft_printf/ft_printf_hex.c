/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:17:13 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 13:56:52 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned int hx, t_opts *opt)
{
	int				len;
	unsigned int	tmp;

	if (opt->dot == 1 && opt->precision == 0 && hx == 0)
		return (0);
	if (hx == 0)
		return (1);
	len = 0;
	tmp = hx;
	while (tmp >= 1)
	{
		tmp /= 16;
		len++;
	}
	return (len);
}

int	print_hex(va_list ap, t_opts *opt)
{
	int				len;
	int				ret;
	unsigned int	num;

	ret = 0;
	num = va_arg(ap, unsigned int);
	len = ft_hexlen(num, opt);
	if (opt->flag != 1)
		ret += print_space_p(opt, len);
	ret += print_zero_p(opt, len);
	ft_putnbr_base(num, opt, &ret);
	if (opt->flag == 1)
		ret += print_space_p(opt, len);
	return (ret);
}

void	ft_putnbr_base(long long nbr, t_opts *opt, int *ret)
{
	long long		tmp;
	char			*base;

	tmp = nbr;
	base = SHEXC;
	if (tmp == 0 && !(opt->dot == 1 && opt->precision == 0))
	{
		ft_putchar('0');
		(*ret)++;
		return ;
	}
	if (nbr < 0)
		nbr *= (-1);
	if (opt->type == 6)
		base = LHEXC;
	if (nbr > 0)
	{
		if (nbr >= 16)
			ft_putnbr_base(nbr / 16, opt, ret);
		ft_putchar(base[nbr % 16]);
		(*ret)++;
	}
}
