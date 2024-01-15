/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:21:57 by craimond          #+#    #+#             */
/*   Updated: 2024/01/15 15:01:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_state(t_philo *philo, char *str)
{
	sem_wait(philo->data->print_sem);
	if (philo->stop == 0)
	{
		printf("%-20lu %-10u %s\n", get_time(philo->data->start_time),
			philo->id, str);
	}
	sem_post(philo->data->print_sem);
}
