/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:35:23 by mbraets           #+#    #+#             */
/*   Updated: 2022/05/20 17:18:32 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	while (n > 0)
	{
		*temp_dst++ = *temp_src++;
		n--;
	}	
	return (dst);
}
