/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:49 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/23 13:08:56 by mbraets          ###   ########.fr       */
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
	// while (ms)
	// {
	// 	if (getnowms() - philo->starving_time > (size_t) philo->data->time_die)
	// 	{
	// 		pthread_mutex_lock(&philo->data->loop_mutex);
	// 		if (philo->data->loop)
	// 			philo_log(philo, LOG_DIE);
	// 		philo->data->loop = false;
	// 		pthread_mutex_unlock(&philo->data->loop_mutex);
	// 		return ;
	// 	}
	// 	usleep(1000);
	// 	--ms;
	// }
}

void	philo_eating(t_philo *philo)
{
	size_t	now;

	pthread_mutex_lock(philo->left);
	philo_log(philo, LOG_TAKEN_FORK);
	pthread_mutex_lock(philo->right);
	now = getnowms();
	if (philo->starving_time == 0)
		philo->starving_time = getnowms();
	if (philo->starving_time - now < (size_t) philo->data->time_die && philo->data->loop)
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

bool	philo_getLoop(t_data *data)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&data->loop_mutex);
	ret = data->loop;
	pthread_mutex_unlock(&data->loop_mutex);
	return (ret);
}

void	philo_setLoop(t_data *data, bool loop)
{
	pthread_mutex_lock(&data->loop_mutex);
	data->loop = loop;
	pthread_mutex_unlock(&data->loop_mutex);
}

void	*routine(void *args)
{
	t_philo	*philo;

	// size_t old = getnowms();
	philo = (t_philo *)args;
	philo->starving_time = getnowms();
	if (philo->index % 2 != 0)
		philo_sleep(philo, philo->data->time_eat);
	// printf("%lu : %d %d mange\n", getnowms() - old, philo->index, philo->index % 2);

	while (philo->state == ALIVE)
	{
		if (philo_getLoop(philo->data))
			return (NULL);
		// philo_eating(philo);
		// if (!philo->state)
		// 	return (NULL);
		philo_sleeping(philo);
		philo_thinking(philo);
		// if (philo->num_of_eat == philo->data->eat_max)

		if (philo->state == DEAD)
		{
			philo_log(philo, LOG_DIE);
			philo_setLoop(philo->data, false);
		}
		
		pthread_mutex_lock(&philo->data->loop_mutex);
	}
	return (NULL);
}
