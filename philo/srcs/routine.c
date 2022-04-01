/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:49 by mbraets           #+#    #+#             */
/*   Updated: 2022/04/01 11:03:41 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	philo_log(t_philo *philo, char *log)
{
	long long	now_ms;
	t_time		now_time;

	gettimeofday(&now_time, NULL);
	now_ms = time_to_ms(now_time) - time_to_ms(philo->data->start_time);
	printf(log, now_ms, philo->index + 1);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	philo_log(philo, LOG_TAKEN_FORK);
	pthread_mutex_lock(philo->right);
	philo_log(philo, LOG_TAKEN_FORK);
	philo_log(philo, LOG_EATING);
	philo->num_of_eat++;
	if (philo->num_of_eat == philo->data->eat_max)
		philo->data->philos_eat_finish += 1;
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	philo_sleeping(t_philo *philo)
{
	philo_log(philo, LOG_SLEEPING);
	usleep(philo->data->time_sleep * 1000);
	// printf("%d\n", philo->data->time_sleep);
}

void	philo_thinking(t_philo *philo)
{
	philo_log(philo, LOG_THINKING);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->index % 2 == 0)
		usleep(philo->data->time_eat * 1000);
	while (philo->data->loop)
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
		if (philo->num_of_eat == philo->data->eat_max)
			philo->data->loop = false;
	}
	return (NULL);
}
