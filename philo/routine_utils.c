/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:21:57 by craimond          #+#    #+#             */
/*   Updated: 2024/01/15 14:30:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint8_t	is_game_over(t_data *d)
{
	pthread_mutex_lock(&d->game_over_mutex);
	if (d->game_over == 1)
	{
		pthread_mutex_unlock(&d->game_over_mutex);
		return (1);
	}
	pthread_mutex_unlock(&d->game_over_mutex);
	return (0);
}

void	set_game_over(t_data *d)
{
	pthread_mutex_lock(&d->game_over_mutex);
	if (d->game_over == 0)
		d->game_over = 1;
	pthread_mutex_unlock(&d->game_over_mutex);
}

void	print_state(t_data *d, uint32_t id, char *str)
{
	pthread_mutex_lock(&d->game_over_mutex);
	if (d->game_over != 1)
	{
		pthread_mutex_unlock(&d->game_over_mutex);
		pthread_mutex_lock(&d->print_mutex);
		printf("%-20lu %-10u %s\n", get_time(d->start_time), id, str);
		pthread_mutex_unlock(&d->print_mutex);
	}
	pthread_mutex_unlock(&d->game_over_mutex);
}
