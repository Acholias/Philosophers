/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:54:41 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/13 12:12:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_simulation_off(t_data *data)
{
	int	simu_off;

	pthread_mutex_lock(&data->simu_mutex);
	simu_off = data->simu_off;
	pthread_mutex_unlock(&data->simu_mutex);
	return (simu_off);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		full;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		if (check_simulation_off(data) == 1)
			break ;
		full = 0;
		if (check_full(philos, data, &full))
			return (NULL);
		if (data->nb_meals > 0 && full == data->nb_philos)
		{
			pthread_mutex_lock(&data->simu_mutex);
			data->simu_off = 1;
			pthread_mutex_unlock(&data->simu_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

void	start_simulation(t_data *data, t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&philos[i].meal_mutex);
	}
	i = -1;
	while (++i < data->nb_philos)
		pthread_create(&philos[i].thread, NULL, start_routine, &philos[i]);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philos[i].thread, NULL);
}
