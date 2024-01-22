/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:16:39 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/05 14:02:12 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_isspace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	ft_printf_atoi(const char *str, int *i)
{
	int	ret;
	int	sign;

	ret = 0;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '-')
		sign = -1;
	else if (str[*i] == '+')
		sign = 1;
	else if (ft_isdigit(str[*i]))
	{
		ret = str[*i] - '0';
		sign = 1;
	}
	else
		return (0);
	(*i)++;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		ret = ret * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (ret * sign);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}
