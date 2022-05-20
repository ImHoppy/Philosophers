/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:49 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/20 19:49:38 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	getms(struct timeval now)
{
	unsigned long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

unsigned long	getnowms(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (getms(now));
}

void	philo_log(t_philo *philo, char *log)
{
	unsigned long	now_ms;

	pthread_mutex_lock(&philo->data->print_mutex);
	now_ms = getnowms() - getms(philo->data->start_time);
	printf(log, now_ms, philo->index + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_sleep(t_philo *philo, int ms)
{
	while (ms)
	{
		if (getnowms() - philo->starving_time > (unsigned long) philo->data->time_die)
		{
			pthread_mutex_lock(&philo->data->loop_mutex);
			if (philo->data->loop)
				philo_log(philo, LOG_DIE);
			philo->data->loop = false;
			pthread_mutex_unlock(&philo->data->loop_mutex);
			return ;
		}
		usleep(1000);
		--ms;
	}
}

void	philo_eating(t_philo *philo)
{
	unsigned long	now;

	pthread_mutex_lock(philo->left);
	philo_log(philo, LOG_TAKEN_FORK);
	pthread_mutex_lock(philo->right);
	now = getnowms();
	if (philo->starving_time == 0)
		philo->starving_time = getnowms();
	if (philo->starving_time - now < (unsigned long) philo->data->time_die && philo->data->loop)
	{
		philo_log(philo, LOG_TAKEN_FORK);
		philo_log(philo, LOG_EATING);
		philo->num_of_eat++;
		if (philo->num_of_eat == philo->data->eat_max)
			philo->data->philos_eat_finish += 1;
		philo_sleep(philo, philo->data->time_eat);
		philo->starving_time = getnowms();
	}
	else
	{
		if (philo->data->loop)
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

	unsigned long old = getnowms();
	philo = (t_philo *)args;
	philo->starving_time = getnowms();
	if (philo->index % 2 != 0)
		philo_sleep(philo, philo->data->time_eat);
	printf("%lu : %d %d mange\n", getnowms() - old, philo->index, philo->index % 2);
	// while (philo->data->loop && philo->state == 0)
	// {
	// 	philo_eating(philo);
	// 	if (philo->state)
	// 		return (NULL);
	// 	philo_sleeping(philo);
	// 	philo_thinking(philo);
	// 	if (philo->num_of_eat == philo->data->eat_max)
	// 		philo->data->loop = false;
	// }
	return (NULL);
}
