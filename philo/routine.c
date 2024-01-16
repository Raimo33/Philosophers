/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:49:31 by craimond          #+#    #+#             */
/*   Updated: 2024/01/16 16:26:54 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *arg);
static void	philo_eat(t_philo *philo);
static void	*check_death(void *arg);

int8_t	routine_start(t_philo **table, t_data d)
{
	uint32_t	i;
	t_philo		*philo;

	philo = *table;
	i = -1;
	while (++i < d.num_philo)
	{
		if (pthread_create(&philo->thread_id, NULL, &routine, philo) == -1)
			return (write(2, "Error: failed to create thread\n", 32) * 0 - 1);
		philo = philo->next;
	}
	return (0);
}

static void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_create(&philo->thread2_id, NULL, &check_death, philo);
	pthread_detach(philo->thread2_id);
	if (philo->id % 2 == 0)
	{
		print_state(philo->data, philo->id, "is thinking");
		usleep(philo->data->time_to_eat * 1000);
	}
	while (!is_game_over(philo->data))
	{
		pthread_mutex_lock(&philo->fork_mutex);
		print_state(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->next->fork_mutex);
		print_state(philo->data, philo->id, "has taken a fork");
		philo_eat(philo);
		pthread_mutex_unlock(&philo->next->fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		print_state(philo->data, philo->id, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_state(philo->data, philo->id, "is thinking");
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	t_data	*d;

	d = philo->data;
	pthread_mutex_lock(&philo->eat_mutex);
	philo->meals_eaten++;
	print_state(philo->data, philo->id, "is eating");
	philo->meal_time = get_time(philo->data->start_time);
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_create(&philo->thread2_id, NULL, &check_death, philo);
	pthread_detach(philo->thread2_id);
	usleep(philo->data->time_to_eat * 1000);
	if (philo->meals_eaten >= d->max_meals && d->max_meals != -1)
	{
		pthread_mutex_lock(&d->finished_mutex);
		if (++(d->num_philo_finished) >= d->num_philo)
			set_game_over(d);
		pthread_mutex_unlock(&d->finished_mutex);
	}
}

static void	*check_death(void *arg)
{
	t_philo		*philo;
	t_data		*d;

	philo = (t_philo *)arg;
	d = philo->data;
	usleep(d->time_to_die * 1000 + 8500);
	pthread_mutex_lock(&philo->eat_mutex);
	if (get_time(d->start_time) - philo->meal_time >= d->time_to_die
		&& !is_game_over(d))
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		set_game_over(d);
		printf("%-20lu %-10u died\n", get_time(d->start_time), philo->id);
	}
	else
		pthread_mutex_unlock(&philo->eat_mutex);
	return (NULL);
}

void	handle_lone_philo(t_data d)
{
	usleep(d.time_to_die * 1000);
	printf("%-20u %-10u died\n", d.time_to_die, 1);
}
