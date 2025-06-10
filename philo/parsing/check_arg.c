/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:23:48 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 23:58:04 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse_input(int argc, char **argv)
{
	int		index;
	int		j;
	long	val;

	index = 1;
	while (index < argc)
	{
		j = 0;
		if (argv[index][j] == '+')
			j++;
		while (argv[index][j])
		{
			if (argv[index][j] < '0' || argv[index][j] > '9')
				return (KO);
			j++;
		}
		val = ft_atol(argv[index]);
		if (val <= 0 || val > INT_MAX)
			return (KO);
		index++;
	}
	return (OK);
}

int	is_str_digit(char *str)
{
	int	index;

	index = 0;
	if (!str || !str[index])
		return (0);
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	if (argc == 5)
	{
		if (!is_str_digit(argv[1]) || !is_str_digit(argv[2])
			|| !is_str_digit(argv[3]) || !is_str_digit(argv[4]))
			return (KO);
	}
	if (argc == 6)
	{
		if (!is_str_digit(argv[1]) || !is_str_digit(argv[2])
			|| !is_str_digit(argv[3]) || !is_str_digit(argv[4])
			|| !is_str_digit(argv[5]))
			return (KO);
	}
	return (OK);
}

int	parse_arg(int argc, char **argv)
{
	if (argc < 5)
	{
		print_helper("Wrong arguments: Not enough arguments !");
		return (KO);
	}
	else if (argc > 6)
	{
		print_helper("Wrong arguments: Too many arguments !");
		return (KO);
	}
	if (check_arg(argc, argv) == KO)
	{
		error_digit_arg();
		return (KO);
	}
	return (OK);
}
