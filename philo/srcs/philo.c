/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:28 by mbraets           #+#    #+#             */
/*   Updated: 2022/06/01 15:29:12 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * TODO:
 *  separer  les usleep pour check si il meurt pas dans son sommeil
 *  mutex les display
 */

/**
 * TEST:
 *  5 800 200 200 -> never die
 *  5 800 200 200 7
 *  4 410 200 200 -> never die
 *  4 310 200 100 -> one die
 */
int	philo_parse(t_data *data, int ac, char **av)
{
	if ((ac != 5) & (ac != 6))
		return (1);
	ft_memcpy(data, &(t_data){.philo_max = ft_atoi(av[1]),
		.time_die = ft_atoi(av[2]), .time_eat = ft_atoi(av[3]),
		.time_sleep = ft_atoi(av[4]), .eat_max = ft_atoi(av[5]), .loop = true},
		sizeof(t_data));
	if (data->philo_max < 1
		|| data->time_die < 1
		|| data->time_eat < 1
		|| data->time_sleep < 1
		|| (ac == 6 && data->eat_max <= 0))
		return (1);
	return (0);
}

int	philo_init_mutex(t_data *data)
{
	size_t	i;

	if (ft_palloc(&data->forks, data->philo_max * sizeof(t_forks)))
		return (1);
	i = 0;
	while (i < data->philo_max)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->loop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->philo_finish_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_lock(&data->start_mutex) != 0)
		return (1);
	return (0);
}

int	philo_init(t_data *data)
{
	size_t	i;

	if (ft_palloc(&data->philos, data->philo_max * sizeof(t_philo *)))
		return (1);
	i = 0;
	while (i < data->philo_max)
	{
		if (ft_palloc(&data->philos[i], sizeof(t_philo) * 1))
			return (1);
		ft_memcpy(data->philos[i], &(t_philo){.index = i, .data = data,
			.right = &data->forks[i], .state = ALIVE}, sizeof(t_philo));
		if (pthread_create(&data->philos[i]->thread, NULL, &routine,
				data->philos[i]))
		{
			write(2, "error init thread\n", 18);
			data->loop = false;
			return (philo_wait_thread(data), 2);
		}
		if (i == 0)
			data->philos[i]->left = &data->forks[data->philo_max - 1];
		else
			data->philos[i]->left = &data->forks[i - 1];
		i++;
	}	
	return (0);
}

int	philo_wait_thread(t_data *data)
{
	size_t	i;

	pthread_mutex_unlock(&data->start_mutex);
	gettimeofday(&data->start_time, NULL);
	i = 0;
	while (data->philos[i] && i < data->philo_max)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (philo_parse(&data, ac, av) == 1)
		return (write(2, "Error\n", 6), 1);
	if (data.philo_max == 1)
		return (printf(LOG_DIE, data.time_die, 1), 0);
	if (philo_init_mutex(&data) == 1)
		return (philo_free_struct(&data), 1);
	if (philo_init(&data) == 1)
		return (philo_free_struct(&data), 1);
	if (philo_wait_thread(&data) == 1)
		return (philo_free_struct(&data), 1);
	philo_free_struct(&data);
	return (0);
}
