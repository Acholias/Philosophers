/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:59:23 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/10 23:57:02 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "philo.h"

//error.c
void	print_helper(char *message);
void	error_digit_arg(void);

//utils.c
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);

//convert_utils.c
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

//check_arg.c
int		parse_input(int argc, char **argv);
int		is_str_digit(char *str);
int		check_arg(int argc, char **argv);
int		parse_arg(int argc, char **argv);

//setup_data.c
int		init_data(t_data *data, int argc, char **argv);
t_philo	*init_philos(t_data *data);

#endif