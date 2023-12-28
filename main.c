/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:46:03 by craimond          #+#    #+#             */
/*   Updated: 2023/12/28 16:37:45 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		*routine(void *arg);
static int8_t	check_args(int argc, char **argv);
static uint8_t	routine_start(t_philo **table, t_params p);
static uint8_t 	init_table(t_params p, t_philo **table);
static void		init(t_params *p, char **argv, int8_t is_max_meals);
static void		threads_wait(t_philo **table, t_params p);

int main(int argc, char **argv)
{
	int8_t		out;
	t_params	params;
	t_philo		**table;

	out = check_args(argc, argv);
	if (out > 0)
		return (out);
	init(&params, argv, out);
	table = malloc(sizeof(t_philo *) * params.num_philo);
	out = init_table(params, table);
	if (out > 0)
		return (out);
	out = routine_start(table, params);
	if (out > 0)
		return (out);
	threads_wait(table, params);
}

static void	threads_wait(t_philo **table, t_params p)
{
	t_philo		*philo;
	void		*exit_status;
	uint32_t 	i;

	philo = *table;
	i = 0;
	while(++i <= p.num_philo)
	{
		pthread_join(philo->thread_id, &exit_status);
		if ((uintptr_t)exit_status == 1)
			printf("%lu %u died\n", get_time(), philo->id);
		philo = philo->next;
	}
}

static void	*routine(void *arg)
{
	t_philo		*philo;
	t_params	p;
	uint64_t	bedtime;
	int32_t		num_meals;

	philo = (t_philo *)arg;
	p = *philo->params;
	bedtime = get_time();
	num_meals = 0;
	while (1)
	{
		if (philo->next != philo && philo->status == THINKING && (philo->next->status != EATING || philo->prev->status != EATING))
		{
			philo->status = EATING;
			printf("%lu %u has taken a fork\n", get_time(), philo->id);
			printf("%lu %u has taken a fork\n", get_time(), philo->id);
			printf("%lu %u is eating\n", get_time(), philo->id);
			num_meals++;
			if (get_time() - bedtime > p.time_to_die)
				return ((void *)1);
			if (p.max_meals >= 0 && num_meals >= p.max_meals)
				return ((void *)2);
		}
		if (philo->next != philo && philo->status == EATING)
		{
			usleep(p.time_to_eat);
			philo->status = SLEEPING;
			printf("%lu %u is sleeping\n", get_time(), philo->id);
			bedtime = get_time();
		}
		if (philo->next != philo && philo->status == SLEEPING)
		{
			usleep(p.time_to_sleep);
			philo->status = THINKING;
			printf("%lu %u is thinking\n", get_time(), philo->id);
		}
	}

} //ogni 9 ms fare un check del tempo (per fare cio devi mettere bedtime nella struttura del filosofo e creare un extra thread (waiter) che controlli ogni 9ms se i filosofi sono morti)

static uint8_t	routine_start(t_philo **table, t_params p)
{
	uint32_t	i;
	t_philo		*philo;

	philo = *table;
	i = -1;
	while (++i < p.num_philo)
	{
		if (pthread_create(&philo->thread_id, NULL, &routine, philo) == -1)
			return (write(2, "Error: failed to create thread\n", 32) * 0 + 6);
		philo = philo->next;
	}
	return (0);
}

static uint8_t init_table(t_params p, t_philo **table)
{
	uint32_t	i;
	t_philo		*new_philo;
	t_philo		*first;
	t_philo		*prev;

	prev = NULL;
	i = 0;
	while (++i <= p.num_philo)
	{
		new_philo = lst_new(&p, i);
		if (!new_philo)
			return (write(2, "Error: failed to allocate memory\n", 34) * 0 + 5);
		if (i == 1)
			first = new_philo;
		new_philo->next = *table;
		new_philo->prev = prev;
		prev = new_philo;
		*table = new_philo;
	}
	new_philo->next = first;
	return (0);
}

static void	init(t_params *p, char **argv, int8_t is_max_meals)
{
	p->num_philo = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->max_meals = -1;
	if (is_max_meals)
		p->max_meals = ft_atoi(argv[5]);
}

static int8_t	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Error: Invalid number of arguments\n", 28) * 0 + 1);
	if (argv[1][0] == '0' || argv[1][0] == '-')
		return (write(2, "Error: Invalid n of philosophers\n", 32) * 0 + 2);
	if (argv[2][0] == '-' || argv[3][0] == '-' || argv[4][0] == '-')
		return (write(2, "Error: Invalid time(s) format\n", 24) * 0 + 3);
	if (argv[5])
	{
		if (argv[5][0] == '0' || argv[5][0] == '-')
			return (write(2, "Invalid number of meals\n", 41) * 0 + 4);
		return (-1);
	}
	return (0);
}


