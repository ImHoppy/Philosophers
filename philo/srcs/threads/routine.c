/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:49 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/23 17:21:03 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (philo_getloop(philo->data) == true)
		philo_log(philo, LOG_TAKEN_FORK);
	pthread_mutex_lock(philo->right);
	if (philo_getloop(philo->data) == true)
		philo_log(philo, LOG_TAKEN_FORK);
	if (getnowms() - philo->starving_time < philo->data->time_die && \
	philo_getloop(philo->data))
	{
		philo_log(philo, LOG_EATING);
		philo->num_of_eat++;
		if (philo->num_of_eat == philo->data->eat_max && philo->state == ALIVE)
		{
			philo->state = FINISH;
			philo_addfinish(philo->data);
		}
		philo_sleep(philo, philo->data->time_eat);
		philo->starving_time = getnowms();
	}
	else
		philo->state = DEAD;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	philo_sleeping(t_philo *philo)
{
	if (philo_getloop(philo->data) || philo->state == FINISH)
		philo_log(philo, LOG_SLEEPING);
	philo_sleep(philo, philo->data->time_sleep);
}

void	philo_thinking(t_philo *philo)
{
	if (philo_getloop(philo->data) || philo->state == FINISH)
		philo_log(philo, LOG_THINKING);
}

static bool	check_end(t_philo *philo)
{
	if (philo->state == DEAD || philo_getloop(philo->data) == false)
	{
		if (philo_getloop(philo->data))
			philo_log(philo, LOG_DIE);
		return (true);
	}
	return (false);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	philo->starving_time = getnowms();
	if (philo->index % 2 != 0)
		philo_sleep(philo, philo->data->time_eat);
	while (philo->state != DEAD && philo_getloop(philo->data))
	{
		if (philo_getloop(philo->data) == false)
			return (NULL);
		philo_eating(philo);
		if (check_end(philo))
			break ;
		if (philo_getfinish(philo->data) == philo->data->philo_max)
			break ;
		philo_sleeping(philo);
		philo_thinking(philo);
		if (check_end(philo))
			break ;
	}
	philo_setloop(philo->data, false);
	return (NULL);
}
