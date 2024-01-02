/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:49:31 by craimond          #+#    #+#             */
/*   Updated: 2024/01/02 18:08:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void		routine(t_philo *philo);
static void		philo_eat(t_philo *philo);
static void		*check_death(void *arg);

int8_t routine_start(t_philo **table, t_data d)
{
	uint32_t	i;
	t_philo		*philo;

	philo = *table;
	i = -1;
	while (++i < d.num_philo)
	{
		philo->process_id = fork();
		if (philo->process_id == -1)
			return (write(2, "Error: failed to create process\n", 33) * 0 - 1);
		if (philo->process_id == 0)
			routine(philo);
		philo = philo->next;
	}
	return (0);
}

static void	routine(t_philo *philo)
{
	t_philo	*priority_philo;

	pthread_create(&philo->thread_id, NULL, &check_death, philo);
	pthread_detach(philo->thread_id);
	if (philo->id % 2 == 0)
	{
		print_state(philo->data, philo->id, "is thinking");
		usleep(philo->data->time_to_eat * 1000);
	}
	while (1)
	{
		if (philo == priority_philo)
		{
			sem_wait(philo->data->forks_pool);
			print_state(philo->data, philo->id, "has taken a fork");
			sem_wait(philo->data->forks_pool);
			print_state(philo->data, philo->id, "has taken a fork");
			philo_eat(philo);
			sem_post(philo->data->forks_pool);
			sem_post(philo->data->forks_pool);
			print_state(philo->data, philo->id, "is sleeping");
			usleep(philo->data->time_to_sleep * 1000);
			print_state(philo->data, philo->id, "is thinking");
		}
	}
}

static void	philo_eat(t_philo *philo)
{
	philo->meals_eaten++;
	pthread_create(&philo->thread_id, NULL, &check_death, philo);
	pthread_detach(philo->thread_id);
	print_state(philo->data, philo->id, "is eating");
	sem_wait(philo->meal_time_sem);
	philo->meal_time = get_time(philo->data->start_time);
	sem_post(philo->meal_time_sem);
	usleep(philo->data->time_to_eat * 1000);
}

static void	*check_death(void *arg)
{
	t_philo		*philo;
	t_data		*d;

	philo = (t_philo *)arg;
	d = philo->data;
	usleep(d->time_to_die * 1000 + 8000);
	sem_wait(philo->meal_time_sem);
	if (get_time(d->start_time) - philo->meal_time >= d->time_to_die)
	{
		print_state(d, philo->id, "died");
		destroy_and_free(d);
		exit(1);
	}
	else if (philo->meals_eaten >= philo->data->max_meals && philo->data->max_meals != -1)
	{
		destroy_and_free(d);
		exit(2);
	}
	sem_post(philo->meal_time_sem);
	return (NULL);
}

void handle_lone_philo(t_data d)
{
	usleep(d.time_to_die * 1000);
	printf("%-20u %-10u died\n", d.time_to_die, 1);
}
