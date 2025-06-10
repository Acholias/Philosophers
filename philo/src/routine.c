/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:45:03 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 19:05:18 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long int time_in_ms)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
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
	// if (philo->left_fork < philo->right_fork && philo->data->nb_philos % 2 == 0)
	if (philo->left_fork < philo->right_fork)
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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	lock_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	if (philo->data->nb_philos == 1)
	{
		ft_usleep(1);
		pthread_mutex_unlock(first);
		return ;
	}
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	print_action(philo, "is eating");
	philo->nb_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	philo_sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->t_sleep);
	print_action(philo, "is thinking");
}

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

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
