/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:35:10 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/19 16:37:16 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;
	char	*p;

	p = (char *)s;
	cc = (char)c;
	while (*p && *p != cc)
		p++;
	if (*p == cc)
		return (p);
	return (NULL);
}
