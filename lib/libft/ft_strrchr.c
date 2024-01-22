/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:43:51 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/19 22:08:05 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
