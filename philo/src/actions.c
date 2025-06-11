/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:39:07 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/11 14:39:17 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	lock_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	print_action(philo, MSG_FORK);
	pthread_mutex_lock(second);
	print_action(philo, MSG_FORK);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	print_action(philo, MSG_EAT);
	philo->nb_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	philo_sleep_and_think(t_philo *philo)
{
	print_action(philo, MSG_SLEEP);
	ft_usleep(philo->data->t_sleep);
	print_action(philo, MSG_THINK);
}
