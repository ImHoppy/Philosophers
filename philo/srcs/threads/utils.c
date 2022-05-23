/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:33:16 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/23 16:42:06 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	getms(struct timeval now)
{
	size_t		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

size_t	getnowms(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (getms(now));
}

void	philo_log(t_philo *philo, char *log)
{
	size_t	now_ms;

	pthread_mutex_lock(&philo->data->print_mutex);
	now_ms = getnowms() - getms(philo->data->start_time);
	printf(log, now_ms, philo->index + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_sleep(t_philo *philo, int ms)
{
	size_t	sleep;

	sleep = getnowms() + ms;
	while (getnowms() < sleep)
	{
		if (getnowms() - philo->starving_time > philo->data->time_die)
		{
			pthread_mutex_lock(&philo->data->loop_mutex);
			if (philo->data->loop)
				philo_log(philo, LOG_DIE);
			philo->data->loop = false;
			pthread_mutex_unlock(&philo->data->loop_mutex);
			return ;
		}
		usleep(100);
	}
}
