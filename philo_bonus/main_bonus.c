/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:46:03 by craimond          #+#    #+#             */
/*   Updated: 2024/01/02 18:39:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int8_t	check_args(int argc, char **argv);
static int8_t	init(t_data *d, char **argv, int8_t is_max_meals);
static int8_t	init_table(t_data *d, t_philo **table);
static void		wait_processes(t_data d, t_philo **table);

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
		return (-1 * (data->num_philo != 1));
	table = malloc(sizeof(t_philo *) * data->num_philo);
	if (!table)
		return (write(2, "Error: failed to allocate memory\n", 34) * 0 - 1);
	if (init_table(data, table) == -1 || routine_start(table, *data) == -1)
	{
		destroy_and_free(data);
		return (-1);
	}
	wait_processes(*data, table);
	destroy_and_free(data);
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
	sem_unlink("/forks_pool");
	sem_unlink("/print");
	d->forks_pool = sem_open("/forks_pool", O_CREAT, 0644, d->num_philo);
	d->print_sem = sem_open("/print", O_CREAT, 0644, 1);
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
	d->table = table;
	return (0);
}

static void	wait_processes(t_data d, t_philo **table)
{
	uint32_t	i;
	uint32_t	j;
	int32_t		status;
	t_philo		*philo;

	i = 0;
	while (++i <= d.num_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			philo = *table;
			j = 0;
			while (++j <= d.num_philo)
			{
				kill(philo->process_id, SIGKILL);
				philo = philo->next;
			}
			break ;
		}
	}
}
