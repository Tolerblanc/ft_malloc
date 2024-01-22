/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:30:01 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/19 21:01:06 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (dst == NULL && src == NULL)
		return (NULL);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	while (n--)
		*p1++ = *p2++;
	return (dst);
}
