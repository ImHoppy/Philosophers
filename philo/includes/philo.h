/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/25 13:06:20 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define LOG_TAKEN_FORK	= "%d %d has taken a fork\n"
# define LOG_EATING		= "%d %d is eating\n"
# define LOG_SLEEPING	= "%d %d is sleeping\n"
# define LOG_THINKING	= "%d %d is thinking\n"
# define LOG_DIE		= "%d %d died\n"

typedef struct s_philo {
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				index;
}	t_philo;

typedef struct s_data {
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	unsigned int	philo_max;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	eat_max;
}	t_data;

int	ft_atoi(const char *str);

#endif

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/