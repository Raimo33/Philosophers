/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:48:05 by craimond          #+#    #+#             */
/*   Updated: 2024/01/16 16:21:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nptr)
{
	long	n;
	char	sign;

	n = 0;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	sign = nptr[0];
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr != '\0' && *nptr <= '9' && *nptr >= '0')
	{
		n *= 10;
		n += (*nptr++ - 48);
	}
	n = (-n) * (sign == '-') + (n) * (sign != '-');
	if (n > INT32_MAX)
		n = INT32_MAX;
	else if (n < INT32_MIN)
	{
		n = INT32_MIN;
	}
	return ((int)n);
}

uint64_t	get_time(uint64_t start)
{
	struct timeval	times;

	gettimeofday(&times, NULL);
	return ((uint64_t)((times.tv_sec * 1000 + times.tv_usec / 1000) - start));
}

void	destroy_and_free(t_data *data, t_philo **table)
{
	pthread_mutex_unlock(&data->game_over_mutex);
	pthread_mutex_destroy(&data->game_over_mutex);
	lst_clear(table, data->num_philo);
	pthread_mutex_unlock(&data->finished_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	free(data);
}
