/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:46:03 by craimond          #+#    #+#             */
/*   Updated: 2024/01/16 16:21:24 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int8_t	check_args(int argc, char **argv);
static int8_t	init(t_data *d, char **argv, int8_t is_max_meals);
static int8_t	init_table(t_data *d, t_philo **table);
static void		join_threads(uint32_t num_philo, t_philo *philo);

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			**table;

	if (check_args(argc, argv) == -1)
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error: failed to allocate memory\n", 34) * 0 - 1);
	if (init(data, argv, (argv[5] != NULL)) == -1)
	{
		free(data);
		return (-1 * (argv[1][0] != '1'));
	}
	table = malloc(sizeof(t_philo *) * data->num_philo);
	if (!table)
		return (write(2, "Error: failed to allocate memory\n", 34) * 0 - 1);
	if (init_table(data, table) == -1 || routine_start(table, *data) == -1)
	{
		destroy_and_free(data, table);
		return (-1);
	}
	join_threads(ft_atoi(argv[1]), *table);
	usleep(data->time_to_die * 1000 + 1000);
	destroy_and_free(data, table);
	return (0);
}

static int8_t	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Error: Invalid number of arguments\n", 36) * 0 - 1);
	if (argv[1][0] == '0' || argv[1][0] == '-')
		return (write(2, "Error: Invalid n of philosophers\n", 32) * 0 - 1);
	if (argv[2][0] == '-' || argv[3][0] == '-' || argv[4][0] == '-')
		return (write(2, "Error: Invalid time(s) format\n", 24) * 0 - 1);
	if (argv[5] && (argv[5][0] == '0' || argv[5][0] == '-'))
		return (write(2, "Invalid number of meals\n", 25) * 0 - 1);
	return (0);
}

static int8_t	init(t_data *d, char **argv, int8_t is_max_meals)
{
	d->num_philo = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	if (d->num_philo == 1)
	{
		handle_lone_philo(*d);
		return (-1);
	}
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	d->max_meals = -1;
	if (is_max_meals == 1)
		d->max_meals = ft_atoi(argv[5]);
	d->start_time = get_time(0);
	if (pthread_mutex_init(&d->game_over_mutex, NULL) != 0
		|| pthread_mutex_init(&d->finished_mutex, NULL) != 0
		|| pthread_mutex_init(&d->print_mutex, NULL) != 0)
		return (write(2, "Error: failed to initialize mutex\n", 35) * 0 - 1);
	d->num_philo_finished = 0;
	d->game_over = 0;
	return (0);
}

static int8_t	init_table(t_data *d, t_philo **table)
{
	uint32_t	i;
	t_philo		*new_philo;
	t_philo		*prev;

	prev = NULL;
	i = 0;
	while (++i <= d->num_philo)
	{
		new_philo = lst_new(i, d);
		if (!new_philo)
			return (write(2, "Error: failed to allocate memory\n", 34) * 0 - 1);
		if (i == 1)
			(*table) = new_philo;
		new_philo->prev = prev;
		if (i > 1)
			prev->next = new_philo;
		prev = new_philo;
	}
	(*table)->prev = prev;
	prev->next = (*table);
	return (0);
}

static void	join_threads(uint32_t num_philo, t_philo *philo)
{
	uint32_t	i;

	i = -1;
	while (++i < num_philo)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
	}
}
