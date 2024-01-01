/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:21:57 by craimond          #+#    #+#             */
/*   Updated: 2024/01/01 18:19:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

uint8_t	is_game_over(t_data *d)
{
	sem_wait(d->game_over_sem);
	if (d->game_over == 1)
	{
		sem_post(d->game_over_sem);
		return (1);
	}
	sem_post(d->game_over_sem);
	return (0);
}

void set_game_over(t_data *d)
{
	sem_wait(d->game_over_sem);
	if (d->game_over == 0)
		d->game_over = 1;
	sem_post(d->game_over_sem);
}

void print_state(t_data *d, uint32_t id, char *str)
{
	if (d->game_over != 1)
		printf("%-20lu %-10u %s\n", get_time(d->start_time), id, str);
}
