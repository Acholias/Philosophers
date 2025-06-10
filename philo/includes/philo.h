/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:17:02 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 23:13:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include "typedef.h"
# include "parsing.h"

//actions.c
void		ft_usleep(long int time_in_ms);
void		philo_eat(t_philo *philo);
void		philo_sleep_and_think(t_philo *philo);

//routine.c
long int	get_time(void);
void		print_action(t_philo *philo, const char *action);
void		lock_forks(t_philo *philo, pthread_mutex_t **first,
				pthread_mutex_t **second);
void		*start_routine(void *arg);

//check_simulation.c
int			check_meals(t_philo *philo);
int			check_full(t_philo *philos, t_data *data, int *full);
int			check_death(t_philo *philos, t_data *data, int i);

//launch_monitoring.c
void		*monitor_routine(void *arg);
void		start_simulation(t_data *data, t_philo *philos);

//destroy_thread.c
void		cleanup_thread(t_data *data, t_philo *philos);

#endif