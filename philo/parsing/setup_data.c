/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:53:35 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/13 12:35:26 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_data_mutex(t_data *data)
{
	int	index;

	index = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (KO);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->simu_mutex, NULL);

	while (index < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[index], NULL);
		index++;
	}
	return (OK);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_input(argc, argv) == KO)
	{
		print_helper("Wrong arguments: invalid or out-of-range value");
		return (KO);
	}
	data->nb_philos = ft_atoi(argv[1]);
	if (data->nb_philos <= 0)
	{
		print_helper
		("Wrong arguments: The number of philosophers must be > 0");
		return (KO);
	}
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->nb_meals = -1;
	else if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	data->simu_off = 0;
	if (init_data_mutex(data) == KO)
		return (KO);
	return (OK);
}

static void	init_philo_values(t_philo *philo, t_data *data, int index)
{
	philo->id = index + 1;
	philo->nb_meals_eaten = 0;
	philo->last_meal = data->start_time;
	philo->left_fork = &data->forks[index];
	philo->right_fork = &data->forks[(index + 1) % data->nb_philos];
	philo->data = data;
	pthread_mutex_init(&philo->meal_mutex, NULL);
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
		init_philo_values(&philos[index], data, index);
		index++;
	}
	return (philos);
}
