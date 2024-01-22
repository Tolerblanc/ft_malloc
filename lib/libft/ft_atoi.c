/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:54:00 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/19 22:23:26 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	else if (*str == '+')
		sign = 1;
	else if (ft_isdigit(*str))
		num = *str - '0';
	else
		return (0);
	str++;
	while (*str && ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (sign * num);
}
