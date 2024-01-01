/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:48:05 by craimond          #+#    #+#             */
/*   Updated: 2024/01/01 18:34:16 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int ft_atoi(char *nptr)
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
	struct timeval times;

	gettimeofday(&times, NULL);
	return ((uint64_t)((times.tv_sec * 1000 + times.tv_usec / 1000) - start));
}

void	destroy_and_free(t_data *data, t_philo **table)
{
	sem_close(data->forks_pool);
	sem_close(data->finished_sem);
	sem_close(data->game_over_sem);
	sem_unlink("/forks_pool");
	sem_unlink("/finished");
	sem_unlink("/game_over");
	lst_clear(table, *data);
	free(data);
}
