/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/30 19:45:15 by mbraets          ###   ########.fr       */
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

typedef pthread_mutex_t	t_forks;
typedef struct timeval	t_time;

typedef struct s_philo {
	struct s_data		*data;
	pthread_t	thread_id;
	t_forks		*left;
	t_forks		*right;
	int			state;
	int			index;
	int			num_of_eat;
}	t_philo;


typedef struct s_data {
	t_philo		**philos;
	t_forks		**forks;
	t_time		start_time;
	int			philo_max;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			eat_max;
}	t_data;



int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	philo_free_struct(t_data *data);

#endif

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/