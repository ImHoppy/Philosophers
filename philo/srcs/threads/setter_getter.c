/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:35:45 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/23 16:45:00 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_getloop(t_data *data)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&data->loop_mutex);
	ret = data->loop;
	pthread_mutex_unlock(&data->loop_mutex);
	return (ret);
}

void	philo_setloop(t_data *data, bool loop)
{
	pthread_mutex_lock(&data->loop_mutex);
	data->loop = loop;
	pthread_mutex_unlock(&data->loop_mutex);
}

void	philo_addfinish(t_data *data)
{
	pthread_mutex_lock(&data->loop_mutex);
	data->philo_finish++;
	pthread_mutex_unlock(&data->loop_mutex);
}

size_t	philo_getfinish(t_data *data)
{
	size_t	ret;

	ret = 0;
	pthread_mutex_lock(&data->loop_mutex);
	ret = data->philo_finish;
	pthread_mutex_unlock(&data->loop_mutex);
	return (ret);
}
