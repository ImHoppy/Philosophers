/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:28 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/25 15:47:56 by mbraets          ###   ########.fr       */
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

int	philo_init(t_data *data)
{
	int	i;

	data->philos = (t_philo **)ft_calloc(data->philo_max, sizeof(t_philo *));
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->philo_max)
	{
		data->philos[i] = (t_philo *)ft_calloc(1, sizeof(t_philo));
		if (!data->philos[i])
			return (1);
		i++;
	}
	data->forks = (t_forks **)ft_calloc(data->philo_max, sizeof(t_forks *));
	i = 0;
	while (i < data->philo_max)
	{
		data->forks[i] = (t_forks *)ft_calloc(1, sizeof(t_forks));
		if (!data->forks[i])
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
	if (philo_init(&data) == 1)
		return (philo_free_struct(&data), 1);
	gettimeofday(&data.start_time, NULL);
	philo_free_struct(&data);
	return (0);
}
