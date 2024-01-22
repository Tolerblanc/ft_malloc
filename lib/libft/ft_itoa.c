/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:08:52 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/20 00:07:57 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	len;

	len = 0;
	if (n < -999999999)
		return (11);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	power(int n, int p)
{
	int	result;

	if (n == 10 && p == 11)
		return (1000000000);
	result = 1;
	while (p > 1)
	{
		result *= n;
		p--;
	}
	return (result);
}

static int	absol(int n, int *div, int *idx, char *array)
{
	if (n > 0)
		return (n);
	if (n < -999999999)
	{
		array[0] = '-';
		array[1] = -(n / 1000000000) + '0';
		*idx += 2;
		*div /= 10;
		return ((n % 1000000000) * (-1));
	}
	*div /= 10;
	array[0] = '-';
	*idx += 1;
	return (-n);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	int		div;
	char	*result;

	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	len = intlen(n);
	div = power(10, len);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	n = absol(n, &div, &i, result);
	while (div != 0)
	{
		result[i] = (n / div) + '0';
		n = n % div;
		div /= 10;
		i++;
	}
	return (result);
}
