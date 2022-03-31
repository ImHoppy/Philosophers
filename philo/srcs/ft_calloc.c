/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:19:03 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/31 11:35:33 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*xmalloc(size_t size)
{
	static int	limit = 0;

	if (limit > 10)
		return (NULL);
	limit++;
	return (malloc(size));
}

int	ft_calloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
	return (0);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;

// 	ptr = malloc(size * count);
// 	if (!ptr)
// 		return (NULL);
// 	memset(ptr, 0, count * size);
// 	return (ptr);
// }
