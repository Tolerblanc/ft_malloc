/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:54:17 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/19 21:13:49 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (*(p + i) == cc)
			return (p + i);
		i++;
	}
	return (NULL);
}
