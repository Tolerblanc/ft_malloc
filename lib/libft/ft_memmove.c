/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:42:38 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/19 21:42:27 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (dst == NULL && src == NULL)
		return (NULL);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	if (p1 < p2)
	{
		while (len--)
			*p1++ = *p2++;
	}
	else
	{
		p1 += len;
		p2 += len;
		while (len--)
			*--p1 = *--p2;
	}
	return (dst);
}
