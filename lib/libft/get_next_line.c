/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:10:20 by hyunjuki          #+#    #+#             */
/*   Updated: 2023/01/26 18:33:42 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*buf_join(char *s1, char *s2)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	free(s1);
	return (joined_str);
}

static char	*read_fd(int fd, char *result)
{
	int		rd_size;
	char	*buf;

	if (!result)
		result = ft_calloc(1, sizeof(char));
	rd_size = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (rd_size > 0)
	{
		rd_size = read(fd, buf, BUFFER_SIZE);
		if (rd_size < 0)
		{
			free(buf);
			free(result);
			return (NULL);
		}
		buf[rd_size] = 0;
		result = buf_join(result, buf);
		if (ft_strchr(result, '\n'))
			break ;
	}
	free(buf);
	return (result);
}

static char	*get_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*set_next(char *buf)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	new = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	if (!new)
		return (NULL);
	j = 0;
	i++;
	while (buf[i])
		new[j++] = buf[i++];
	new[j] = '\0';
	free(buf);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = set_next(buffer);
	return (line);
}
