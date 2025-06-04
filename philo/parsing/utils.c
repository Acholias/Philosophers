/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:02 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/04 12:27:30 by lumugot          ###   ########.fr       */
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

int	ft_atoi(const char *nptr)
{
	size_t	index;
	size_t	conv;
	size_t	count;
	size_t	neg;

	index = 0;
	conv = 0;
	count = 0;
	neg = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || (nptr[index] == 32))
		index++;
	while (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			neg++;
		count++;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
		conv = conv * 10 + nptr[index++] - '0';
	if (count > 1)
		return (0);
	else if (neg == 1)
		return (-conv);
	return (conv);
}
