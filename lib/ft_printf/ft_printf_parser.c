/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:20:03 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 13:59:45 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_struct(t_opts *opt)
{
	opt->flag = -1;
	opt->precision = 0;
	opt->type = 0;
	opt->width = 0;
	opt->dot = 0;
}

int	fill_struct(const char *s, va_list ap, t_opts *o, int *i)
{
	int	temp;

	++(*i);
	while (s[*i] != '\0' && ft_printf_strchr(MAND, s[*i]) == -1)
	{
		temp = *i;
		parse_flag(s, o, i);
		parse_width(s, ap, o, i);
		parse_prec(s, ap, o, i);
		if (temp == *i)
			break ;
	}
	temp = ft_printf_strchr(MAND, s[*i]);
	if (temp == -1 || temp == 9)
		return (-1);
	o->type = temp;
	(*i)++;
	return (1);
}

void	parse_flag(const char *s, t_opts *o, int *i)
{
	if (s[*i] == '-')
	{
		if (o->flag != 1)
			o->flag = 1;
		(*i)++;
	}
	else if (s[*i] == '0' && s[*i - 1] != '.' )
	{
		if (ft_printf_strchr(MAND, s[*i - 1] != -1))
		{
			if (o->flag != 0)
				o->flag = 0;
			(*i)++;
		}
	}
}

void	parse_prec(const char *s, va_list ap, t_opts *o, int *i)
{
	int	tmp;

	if (s[*i] == '.' && !(o->precision))
	{
		(*i)++;
		o->dot = 1;
		if (ft_printf_strchr(DIGIT, s[*i]) != -1)
			o->precision = ft_printf_atoi(s, i);
		else if (ft_printf_strchr(MAND, s[*i]) != -1)
			o->precision = 0;
		else if (s[*i] == '*')
		{
			tmp = va_arg(ap, int);
			o->precision = (tmp >= 0) ? tmp : 0;
			if (tmp != 0)
				o->dot = 0;
			(*i)++;
		}
		else
			(*i)--;
	}
}

void	parse_width(const char *s, va_list ap, t_opts *o, int *i)
{
	int	tmp;

	if (!(o->width) && !(o->precision))
	{
		if (ft_printf_strchr(DIGIT, s[*i]) != -1 && s[*i - 1] != '.')
			o->width = ft_printf_atoi(s, i);
		else if (s[*i] == '*' && s[*i - 1] != '.')
		{
			tmp = va_arg(ap, int);
			if (tmp >= 0)
				o->width = tmp;
			else
			{
				o->width = (-1) * tmp;
				o->flag = 1;
			}
			(*i)++;
		}
	}
}
