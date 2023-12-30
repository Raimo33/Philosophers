/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:49:31 by craimond          #+#    #+#             */
/*   Updated: 2023/12/30 15:43:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *arg);
static void	philo_eat(t_philo *philo);
static void	*check_death(void *arg);

int8_t routine_start(t_philo **table, t_data p)
{
	uint32_t	i;
	t_philo		*philo;

	philo = *table;
	i = -1;
	while (++i < p.num_philo)
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
	if (philo->status == THINKING && philo->next != philo)
	{
		print_state(philo->data, philo->id, "is thinking");
		usleep(philo->data->time_to_eat * 1000);
	}
	while (philo->status != DEAD && philo->status != FINISHED && !is_game_over(philo->data))
	{
		if (philo->next->status != EATING && philo->prev->status != EATING)
		{
			philo_eat(philo);
			philo->status = SLEEPING;
			print_state(philo->data, philo->id, "is sleeping");
			usleep(philo->data->time_to_sleep * 1000);
			philo->status = THINKING;
			print_state(philo->data, philo->id, "is thinking");
		}
		else
			pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_detach(philo->thread2_id);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	philo->status = EATING;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	philo->meals_eaten++;
	print_state(philo->data, philo->id, "has taken a fork");
	print_state(philo->data, philo->id, "has taken a fork");
	print_state(philo->data, philo->id, "is eating");
	pthread_mutex_lock(&philo->data->meal_time_mutex);
	philo->meal_time = get_time(philo->data->start_time);
	pthread_mutex_unlock(&philo->data->meal_time_mutex);
	pthread_create(&philo->thread2_id, NULL, &check_death, philo);
	usleep(philo->data->time_to_eat * 1000);
}

static void	*check_death(void *arg)
{
	t_philo		*philo;
	t_data		*d;

	philo = (t_philo *)arg;
	d = philo->data;
	usleep(d->time_to_die * 1000 + 1000);
	pthread_mutex_lock(&d->meal_time_mutex);
	if (get_time(d->start_time) - philo->meal_time >= d->time_to_die && !is_game_over(d))
	{
		pthread_mutex_unlock(&d->meal_time_mutex);
		set_game_over(d);
		philo->status = DEAD;
		printf("%-20lu %-10u died\n", get_time(d->start_time), philo->id);
	}
	else if (philo->meals_eaten >= d->max_meals && d->max_meals != -1)
	{
		pthread_mutex_lock(&d->finished_mutex);
		if (++(d->num_philo_finished) >= d->num_philo)
			set_game_over(d);
		pthread_mutex_unlock(&d->finished_mutex);
		philo->status = FINISHED;
	}
	else
		pthread_mutex_unlock(&d->meal_time_mutex);
	return (NULL);
}

void handle_lone_philo(t_data d)
{
	usleep(d.time_to_die * 1000);
	printf("%-20u %-10u died\n", d.time_to_die, 1);
}
