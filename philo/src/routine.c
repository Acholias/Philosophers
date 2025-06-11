/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:45:03 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/11 15:42:23 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, const char *action)
{
	long int	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time() - philo->data->start_time;
	if (!philo->data->simu_off)
		printf("%ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	lock_forks(t_philo *philo, pthread_mutex_t **first,
	pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork
		&& philo->data->nb_philos % 2 == 0)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		print_action(philo, MSG_FORK);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (!philo->data->simu_off)
	{
		if (philo->data->simu_off)
			break ;
		philo_eat(philo);
		if (check_meals(philo))
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
