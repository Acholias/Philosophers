/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:46:14 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 22:57:24 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (parse_arg(argc, argv) == KO || init_data(&data, argc, argv) == KO)
		return (1);
	philos = init_philos(&data);
	if (!philos)
		return (1);
	start_simulation(&data, philos);
	cleanup_thread(&data, philos);
	return (0);
}
