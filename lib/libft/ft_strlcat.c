/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:22:44 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/20 00:07:55 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	while (src[i] && i + 1 + dstlen < dstsize)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	if (dstsize < dstlen)
		return (srclen + dstsize);
	return (dstlen + srclen);
}
