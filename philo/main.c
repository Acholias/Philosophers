/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:10:21 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/04 12:28:34 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (parse_arg(argc, argv) == OK)
	{
		init_data(&data, argc, argv);
		init_philos(&data);
		printf("\033[1;34mWOOOOW c'est beau\n\033[0m");
	}
	else
		return (1);
}
