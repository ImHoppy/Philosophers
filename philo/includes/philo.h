/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:31 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/23 13:08:33 by mbraets          ###   ########.fr       */
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
# include <stdbool.h>

# define LOG_TAKEN_FORK	"%ld %d has taken a fork\n"
# define LOG_EATING		"%ld %d is eating\n"
# define LOG_SLEEPING	"%ld %d is sleeping\n"
# define LOG_THINKING	"%ld %d is thinking\n"
# define LOG_DIE		"%ld %d died\n"

typedef pthread_mutex_t	t_forks;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
enum e_state {
	DEAD,
	ALIVE
};

typedef struct s_philo {
	struct s_data	*data;
	pthread_t		thread;
	t_forks			*left;
	t_forks			*right;
	enum e_state	state;
	size_t			starving_time;
	int				index;
	size_t			num_of_eat;
}	t_philo;

typedef struct s_data {
	t_philo		**philos;
	t_forks		*forks;
	t_mutex		print_mutex;
	t_time		start_time;
	size_t		philo_max;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		eat_max;
	size_t		philos_eat_finish;
	t_mutex		loop_mutex;
	bool		loop;
}	t_data;

int		ft_atoi(const char *str);
void	philo_free_struct(t_data *data);

int		ft_palloc(void *dst, size_t size);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*routine(void *args);

#endif

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/