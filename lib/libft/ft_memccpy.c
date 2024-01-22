/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:56:33 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/14 20:38:44 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)src;
	while ((i < n) && p[i])
	{
		if (p[i] == (unsigned char)c)
		{
			i++;
			ft_memcpy(dst, src, i);
			return (dst + i);
		}
		i++;
	}
	ft_memcpy(dst, src, n);
	return (NULL);
}
