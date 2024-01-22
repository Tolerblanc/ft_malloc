/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:02:15 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/20 18:59:38 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ainstr(char c, char const *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;

	if (!s1)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while ((start < end + 1) && ainstr(s1[start], set))
		start++;
	while (end != 0 && ainstr(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
