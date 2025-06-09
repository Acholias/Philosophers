/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:53:35 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/09 17:50:53 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int	index;

	index = 0;
	data->nb_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	data->simu_off = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return ;
	pthread_mutex_init(&data->print_mutex, NULL);
	while (index < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[index], NULL);
		index++;
	}
}

t_philo	*init_philos(t_data *data)
{
	int		index;
	t_philo	*philos;

	index = 0;
	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (NULL);
	while (index < data->nb_philos)
	{
		philos[index].id = index + 1;
		philos[index].nb_meals_eaten = 0;
		philos[index].last_meal = data->start_time;
		philos[index].left_fork = &data->forks[index];
		philos[index].right_fork = &data->forks[(index + 1) % data->nb_philos];
		philos[index].data = data;
		pthread_mutex_init(&philos[index].meal_mutex, NULL);
		index++;
	}
	return (philos);
}
