/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:19:03 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/25 14:33:02 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*a;

	i = -1;
	a = (unsigned char *) b;
	while (i < len)
		a[i++] = (unsigned char) c;
	b = (void *) a;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
