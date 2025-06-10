/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:46:14 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 18:47:39 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	check_death(t_philo *philos, t_data *data, int i)
{
	long int	last_meal;

	pthread_mutex_lock(&philos[i].meal_mutex);
	last_meal = philos[i].last_meal;
	pthread_mutex_unlock(&philos[i].meal_mutex);
	if ((get_time() - last_meal) >= data->t_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->simu_off)
			printf("%ld %d died\n", get_time() - data->start_time,
				philos[i].id);
		data->simu_off = 1;
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_full(t_philo *philos, t_data *data, int *full)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (data->nb_meals > 0 && philos[i].nb_meals_eaten >= data->nb_meals)
			(*full)++;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (check_death(philos, data, i))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		full;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!data->simu_off)
	{
		full = 0;
		if (check_full(philos, data, &full))
			return (NULL);
		if (data->nb_meals > 0 && full == data->nb_philos)
		{
			data->simu_off = 1;
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

static void	start_simulation(t_data *data, t_philo *philos)
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

static void	cleanup(t_data *data, t_philo *philos)
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
	cleanup(&data, philos);
	return (0);
}
