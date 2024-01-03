/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:37:38 by craimond          #+#    #+#             */
/*   Updated: 2024/01/02 18:32:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*lst_new(uint32_t i, t_data *d)
{
	t_philo		*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->id = i;
	new_philo->meals_eaten = 0;
	new_philo->stop = 0;
	new_philo->thread_id = 0;
	new_philo->thread2_id = 0;
	new_philo->meal_time = 0;
	new_philo->data = d;
	pthread_mutex_init(&new_philo->fork_mutex, NULL);
	pthread_mutex_init(&new_philo->meal_time_mutex, NULL);
	new_philo->next = NULL;
	new_philo->prev = NULL;
	return (new_philo);
}

void	lst_clear(t_philo **table, t_data d)
{
	uint32_t	i;
	t_philo		*philo;
	t_philo		*prev;

	philo = *table;
	i = -1;
	while (++i < d.num_philo)
	{
		prev = philo;
		philo = philo->next;
		pthread_mutex_destroy(&prev->fork_mutex);
		pthread_mutex_destroy(&prev->meal_time_mutex);
		free(prev);
	}
	free(table);
}
