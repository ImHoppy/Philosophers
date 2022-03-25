/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:44:28 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/25 12:37:11 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_parse(t_data *data, int ac, char **av)
{
	if (ac != 5 | ac != 6)
		return (1);
	if (ac == 6)
		data->eat_max = ft_atoi(av[5]);
	*data = (t_data){.philo_max = ft_atoi(av[1]), .time_die = ft_atoi(av[2]),
		.time_eat = ft_atoi(av[3]), .time_sleep = ft_atoi(av[4]),
		.eat_max = (*data).eat_max};

	return (0);
}

int	main(int ac, char **av)
{
	// t_data	data;

	printf("%d\n", ft_atoi("f1"));
	// if (philo_parse(&data, ac, av))
		// return (1);
	(void) ac;
	(void) av;
	return (0);
}
