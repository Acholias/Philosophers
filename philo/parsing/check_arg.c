/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:23:48 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/04 11:56:48 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_helper(char *message)
{
	ft_putstr_fd("\033[1;31m", 2);
	ft_putendl_fd(message, 2);
	ft_putendl_fd("\033[0m", 2);
	ft_putstr_fd(
		"┌───────────────────────────────────────────────────────────────┐\n"
		"\033[1;36m"
		"│                           Usage                               │\n"
		"\033[0m"
		"├───────────────────────────────────────────────────────────────┤\n"
		"│  ./philo nb_philos t_die t_eat t_sleep [nb_meals]             │\n"
		"├───────────────────────────────────────────────────────────────┤\n"
		"│  nb_philos : Number of philosophers                           │\n"
		"│  t_die     : Time to die (ms)                                 │\n"
		"│  t_eat     : Time to eat (ms)                                 │\n"
		"│  t_sleep   : Time to sleep (ms)                               │\n"
		"│  nb_meals  : (optional) Number of meals                       │\n"
		"└───────────────────────────────────────────────────────────────┘\n\n", 2);
}

void	error_digit_arg(void)
{
	ft_putstr_fd("\033[1;31mWrong arguments: Please enter only ", 1);
	ft_putendl_fd("integer numbers !\033[0m", 2);
}

int	is_str_digit(char *str)
{
    int	i = 0;
    if (!str || !str[0])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
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
