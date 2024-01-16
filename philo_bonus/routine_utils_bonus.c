/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:21:57 by craimond          #+#    #+#             */
/*   Updated: 2024/01/16 18:37:23 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_state(t_philo *philo, char *str)
{
	sem_t	*tmp;

	sem_wait(philo->data->print_sem);
	tmp = sem_open("/game_over", 0);
	if (tmp == SEM_FAILED && philo->stop == 0)
	{
		printf("%-20lu %-10u %s\n", get_time(philo->data->start_time),
			philo->id, str);
	}
	else
		sem_close(tmp);
	sem_post(philo->data->print_sem);
}
