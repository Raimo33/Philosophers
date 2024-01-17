/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:21:57 by craimond          #+#    #+#             */
/*   Updated: 2024/01/17 14:57:51 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_state(t_philo *philo, char *str)
{
	sem_wait(philo->data->print_sem);
	if (philo->stop == 0)
	{
		philo->data->game_over_sem = sem_open("/game_over", 0);
		if (philo->data->game_over_sem == SEM_FAILED)
		{
			printf("%-20lu %-10u %s\n", get_time(philo->data->start_time),
				philo->id, str);
		}
		else if (philo->data->game_over_sem != SEM_FAILED)
		{
			philo->stop = 1;
			sem_close(philo->data->game_over_sem);
		}
	}
	else
		sem_close(philo->data->game_over_sem);
	sem_post(philo->data->print_sem);
}
