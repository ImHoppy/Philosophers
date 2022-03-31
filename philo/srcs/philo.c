/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:28 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/31 11:40:37 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_parse(t_data *data, int ac, char **av)
{
	if ((ac != 5) & (ac != 6))
		return (1);
	*data = (t_data){.philo_max = ft_atoi(av[1]), .time_die = ft_atoi(av[2]),
		.time_eat = ft_atoi(av[3]), .time_sleep = ft_atoi(av[4]),
		.eat_max = ft_atoi(av[5])};
	if (data->philo_max < 1
		|| data->time_die < 1
		|| data->time_eat < 1
		|| data->time_sleep < 1
		|| data->eat_max < 0)
		return (1);
	return (0);
}

// void	eat()
// {
// 	mute
	
// }

void	*routine(void *args)
{
	t_data	*data;
	t_time	current_time;

	data = (t_data *)args;
	gettimeofday(&current_time, NULL);
	printf("Hi %ld\n",  current_time.tv_usec - data->start_time.tv_usec);
	return (NULL);
}

int	philo_init(t_data *data)
{
	int	i;

	if (ft_calloc(&data->philos, data->philo_max * sizeof(t_philo *)))
		return (1);
	i = 0;
	while (i < data->philo_max)
	{
		if (ft_calloc(&data->philos[i], 1 * sizeof(t_philo)))
			return (1);
		data->philos[i]->index = i + 1;
		*data->philos[i] = (t_philo){.index = i + 1, .data = data};
		if (pthread_create(&data->philos[i]->thread_id, NULL, &routine, (void *)data) != 0)
			return (1);
		i++;
	}
	if (ft_calloc(&data->forks, data->philo_max * sizeof(t_forks *)))
		return (1);
	i = 0;
	while (i < data->philo_max)
	{
		if (ft_calloc(&data->forks[i], sizeof(t_forks) * 1))
			return (1);
		if (pthread_mutex_init(data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int philo_wait_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_max)
	{
		if (pthread_join(data->philos[i]->thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (philo_parse(&data, ac, av) == 1)
		return (write(2, "Error\n", 6), 1);
	gettimeofday(&data.start_time, NULL);
	if (philo_init(&data) == 1)
		return (philo_free_struct(&data), 1);
	if (philo_wait_thread(&data) == 1)
		return (philo_free_struct(&data), 1);
	philo_free_struct(&data);
	return (0);
}
