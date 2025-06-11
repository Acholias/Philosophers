/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:45:43 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/11 15:37:16 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->nb_meals > 0 && philo->nb_meals_eaten
		>= philo->data->nb_meals)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	check_full(t_philo *philos, t_data *data, int *full)
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

int	check_death(t_philo *philos, t_data *data, int i)
{
	long int	last_meal;

	pthread_mutex_lock(&philos[i].meal_mutex);
	last_meal = philos[i].last_meal;
	pthread_mutex_unlock(&philos[i].meal_mutex);
	if ((get_time() - last_meal) >= data->t_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->simu_off)
			printf("%ld %d %s\n", get_time() - data->start_time,
				philos[i].id, MSG_DIED);
		else
			data->simu_off = 1;
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}
