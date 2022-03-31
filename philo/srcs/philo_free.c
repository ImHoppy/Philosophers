/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:11:20 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/31 13:00:07 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_max && data->philos[i] != NULL)
	{
		free(data->philos[i]);
		i++;
	}
	free(data->philos);
}

int	philo_free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_max && &data->forks[i] != NULL)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (1);
		// free(data->forks[i]);
		i++;
	}
	free(data->forks);
	return (0);
}

void	philo_free_struct(t_data *data)
{
	if (data->philos)
		philo_free_philo(data);
	if (data->forks)
		philo_free_forks(data);
}
