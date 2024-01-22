/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:15:43 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/20 19:11:06 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**freeall(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static void	set_idx(const char *s, size_t *i, size_t *w_len, char c)
{
	*w_len = 1;
	while (s[*i] && s[*i] == c)
		(*i)++;
	while (s[*i + *w_len] && s[*i + *w_len] != c)
		(*w_len)++;
}

char	**ft_split(char const *s1, char c)
{
	char	**result;
	size_t	words;
	size_t	w_len;
	size_t	i;
	size_t	j;

	i = 0;
	words = count_words(s1, c);
	j = words;
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (result == NULL)
		return (NULL);
	result[words] = NULL;
	while (words != 0)
	{
		set_idx(s1, &i, &w_len, c);
		result[j - words] = ft_substr(s1, i, w_len);
		if (result[j - words] == NULL)
			return (freeall(result));
		words--;
		i += w_len;
	}
	return (result);
}
