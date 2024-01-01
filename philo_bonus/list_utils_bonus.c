/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:37:38 by craimond          #+#    #+#             */
/*   Updated: 2024/01/01 18:33:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_philo	*lst_new(uint32_t i, t_data *d)
{
	t_philo		*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->id = i;
    new_philo->meals_eaten = 0;
	new_philo->stop = 0;
	new_philo->process_id = 0;
	new_philo->thread_id = 0;
	new_philo->meal_time = 0;
	new_philo->data = d;
	new_philo->meal_time_sem = sem_open("/meal_time", O_CREAT, 0644, 1);
	new_philo->next = NULL;
	new_philo->prev = NULL;
	return (new_philo);
}

void	lst_clear(t_philo **table, t_data d)
{
	uint32_t 	i;
	t_philo		*philo;
	t_philo		*prev;

	philo = *table;
	i = -1;
	while (++i < d.num_philo)
	{
		prev = philo;
		philo = philo->next;
		sem_close(prev->meal_time_sem);
		sem_unlink("/meal_time");
		free(prev);
	}
	free(table);
}
