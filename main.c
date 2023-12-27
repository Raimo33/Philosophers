/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:46:03 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 19:51:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		init(t_params *p, char **argv, int8_t is_max_meals);
static int8_t	check_args(int argc, char **argv);

int main(int argc, char **argv)
{
	int8_t		out;
	t_params	params;
	t_seat		**table;

	out = check_args(argc, argv);
	if (out > 0)
		return (out);
	init(&params, argv, out);
	init_table(params, table);
}

static void init_table(t_params p, t_seat **table)
{
	uint32_t	i;
	t_seat		*new_seat;
	t_seat		*first;

	i = -1;
	while (++i < p.num_philo)
	{
		new_seat = lst_new(&p, i);
		if (!new_seat)
			return (write(2, "Error: failed to allocate memory\n", 34) * 0 + 5);
		if (i == 0)
			first = new_seat;
		new_seat->next = *table;
		*table = new_seat;
	}
	new_seat->next = first;
}

static void	init(t_params *p, char **argv, int8_t is_max_meals)
{
	p->num_philo = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->num_meals = 0;
	if (is_max_meals)
		p->num_meals = ft_atoi(argv[5]);
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


