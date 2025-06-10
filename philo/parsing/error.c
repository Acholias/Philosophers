/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:55:07 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 23:57:09 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_helper(char *message)
{
	ft_putstr_fd("\033[1;31m", 2);
	ft_putendl_fd(message, 2);
	ft_putendl_fd("\033[0m", 2);
	ft_putendl_fd(
		"┌──────────────────────────────────────────────────────────────┐\n"
		"│                           Usage                              │\n"
		"├──────────────────────────────────────────────────────────────┤\n"
		"│        ./philo nb_philos t_die t_eat t_sleep [nb_meals]      │\n"
		"├──────────────────────────────────────────────────────────────┤\n"
		"│  nb_philos : Number of philosophers (must be > 0)            │\n"
		"│  t_die     : Time to die (ms)                                │\n"
		"│  t_eat     : Time to eat (ms)                                │\n"
		"│  t_sleep   : Time to sleep (ms)                              │\n"
		"│  nb_meals  : (optional) Number of meals                      │\n"
		"└──────────────────────────────────────────────────────────────┘", 2);
}

void	error_digit_arg(void)
{
	ft_putstr_fd("\033[1;31mWrong arguments: Please enter only ", 1);
	ft_putendl_fd("integer numbers !\033[0m", 2);
}
