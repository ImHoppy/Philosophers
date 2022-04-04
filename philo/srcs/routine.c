/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:49 by mbraets           #+#    #+#             */
/*   Updated: 2022/04/04 16:11:45 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	getms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

long long	getnowms(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (getms(now));
}

void	philo_log(t_philo *philo, char *log)
{
	long long	now_ms;
	t_time		now_time;

	gettimeofday(&now_time, NULL);
	now_ms = getms(now_time) - getms(philo->data->start_time);
	printf(log, now_ms, philo->index + 1);
}

void	philo_sleep(t_philo *philo, int ms)
{
	while (ms)
	{
		if (getms(philo->starving_time) + philo->data->time_die > getnowms())
		{
			philo_log(philo, LOG_DIE);
			philo->data->loop = false;
			return ;
		}
		usleep(1000);
		--ms;
	}
}

void	philo_eating(t_philo *philo)
{
	t_time	now;

	pthread_mutex_lock(philo->left);
	philo_log(philo, LOG_TAKEN_FORK);
	pthread_mutex_lock(philo->right);
	gettimeofday(&now, NULL);
	if (getms(philo->starving_time) - getms(now) < philo->data->time_die && philo->data->loop)
	{
		philo_log(philo, LOG_TAKEN_FORK);
		philo_log(philo, LOG_EATING);
		philo->num_of_eat++;
		if (philo->num_of_eat == philo->data->eat_max)
			philo->data->philos_eat_finish += 1;
		philo_sleep(philo, philo->data->time_eat);
		gettimeofday(&philo->starving_time, NULL);
	}
	else
	{
		philo_log(philo, LOG_DIE);
		philo->state = 1;
	}
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	philo_sleeping(t_philo *philo)
{
	philo_log(philo, LOG_SLEEPING);
	philo_sleep(philo, philo->data->time_sleep);
}

void	philo_thinking(t_philo *philo)
{
	philo_log(philo, LOG_THINKING);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->index % 2 != 0)
		usleep(philo->data->time_eat * 1000);
	while (philo->data->loop && philo->state == 0)
	{
		philo_eating(philo);
		if (philo->state)
			return (NULL);
		philo_sleeping(philo);
		philo_thinking(philo);
		if (philo->num_of_eat == philo->data->eat_max)
			philo->data->loop = false;
	}
	return (NULL);
}
