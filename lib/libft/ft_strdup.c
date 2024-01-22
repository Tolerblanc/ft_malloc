/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:13:25 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/14 22:17:43 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, len);
	result[len] = '\0';
	return (result);
}
