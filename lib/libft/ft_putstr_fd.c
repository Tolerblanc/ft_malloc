/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjuki <hyunjuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:23:21 by hyunjuki          #+#    #+#             */
/*   Updated: 2022/12/20 00:06:11 by hyunjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
	{
		ft_putchar_fd('(', fd);
		ft_putchar_fd('n', fd);
		ft_putchar_fd('u', fd);
		ft_putchar_fd('l', fd);
		ft_putchar_fd('l', fd);
		ft_putchar_fd(')', fd);
	}
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
