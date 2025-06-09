/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:10:21 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/09 18:18:58 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*monitor_routine(void *arg)
{
    t_philo	*philos = (t_philo *)arg;
    t_data	*data = philos[0].data;
    int		i;
    int		full;
    long int	last_meal;

    while (!data->simu_off)
    {
        full = 0;
        i = 0;
        while (i < data->nb_philos)
        {
            pthread_mutex_lock(&philos[i].meal_mutex);
            last_meal = philos[i].last_meal;
            if (data->nb_meals > 0 && philos[i].nb_meals_eaten >= data->nb_meals)
                full++;
            pthread_mutex_unlock(&philos[i].meal_mutex);
            if ((get_time() - last_meal) >= data->t_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                if (!data->simu_off)
                    printf("%ld %d died\n", get_time() - data->start_time, philos[i].id);
                data->simu_off = 1;
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            i++;
        }
        if (data->nb_meals > 0 && full == data->nb_philos)
        {
            data->simu_off = 1;
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

int	main(int argc, char **argv)
{
    t_data		data;
    t_philo		*philos;
    pthread_t	monitor;
    int			i;

    if (parse_arg(argc, argv) == KO)
        return (1);
    init_data(&data, argc, argv);
    philos = init_philos(&data);
    if (!philos)
        return (1);
    data.start_time = get_time();
    for (i = 0; i < data.nb_philos; i++)
    {
        pthread_mutex_lock(&philos[i].meal_mutex);
        philos[i].last_meal = data.start_time;
        pthread_mutex_unlock(&philos[i].meal_mutex);
    }
    for (i = 0; i < data.nb_philos; i++)
        pthread_create(&philos[i].thread, NULL, start_routine, &philos[i]);
    pthread_create(&monitor, NULL, monitor_routine, philos);
    pthread_join(monitor, NULL);
    for (i = 0; i < data.nb_philos; i++)
        pthread_join(philos[i].thread, NULL);
    for (i = 0; i < data.nb_philos; i++)
    {
        pthread_mutex_destroy(&data.forks[i]);
        pthread_mutex_destroy(&philos[i].meal_mutex);
    }
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(philos);
    return (0);
}
