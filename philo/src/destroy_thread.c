/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:52:21 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/11 15:09:20 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_thread(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(philos);
}
