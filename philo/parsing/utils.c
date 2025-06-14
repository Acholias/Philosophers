/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:02 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 23:33:23 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (!s || fd < 0)
		return ;
	while (s[index])
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
