/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:19:23 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 23:05:24 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "philo.h"

# define KO 1
# define OK 0

# define MSG_FORK    "has taken a fork 🍴"
# define MSG_EAT     "is eating 🍝"
# define MSG_SLEEP   "is sleeping 💤"
# define MSG_THINK   "is thinking 💭"
# define MSG_DIED    "died 💀"

typedef struct s_data
{
	long int		start_time;
	int				nb_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meals;
	int				simu_off;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals_eaten;
	long int		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

#endif