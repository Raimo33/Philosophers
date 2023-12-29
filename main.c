/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:46:03 by craimond          #+#    #+#             */
/*   Updated: 2023/12/29 19:51:42 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		*routine(void *arg);
static int8_t	check_args(int argc, char **argv);
static uint8_t	routine_start(t_philo **table, t_data d);
static uint8_t 	init_table(t_data *d, t_philo **table);
static uint8_t	init(t_data *d, char **argv, int8_t is_max_meals);
static void		*check_death(void *arg);
static void 	join_threads(t_data d, t_philo *philo);
static void 	print_state(t_data *d, uint32_t id, char *str);
static void 	game_over(t_data *d);

int main(int argc, char **argv)
{
	int8_t			out;
	t_data			*data;
	t_philo			**table;

	out = check_args(argc, argv);
	if (out > 0)
		return (out);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error: failed to allocate memory\n", 34) * 0 + 1);
	out = init(data, argv, out);
	if (out > 0)
		return (out);
	table = malloc(sizeof(t_philo *) * data->num_philo);
	if (!table)
		return (write(2, "Error: failed to allocate memory\n", 34) * 0 + 2);
	out = init_table(data, table);
	if (out > 0)
		return (out);
	out = routine_start(table, *data);
	if (out > 0)
		return (out);
	join_threads(*data, *table);
	pthread_mutex_destroy(&data->can_eat);
	pthread_mutex_destroy(&data->can_set_game_over);
}

static void join_threads(t_data d, t_philo *philo)
{
	uint32_t	i;

	i = -1;
	while (++i < d.num_philo)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
	}
}
static void	*check_death(void *arg)
{
	t_philo		*philo;
	t_data		*d;

	philo = (t_philo *)arg;
	d = philo->data;
	usleep(d->time_to_eat * 1000);
	usleep(d->time_to_die * 1000 + 1000);
	if (philo->status == DEAD)
	{
		printf("%-20lu %-10u died\n", get_time(d->start_time), philo->id);
		game_over(d);
	}
	else if (philo->status == FINISHED)
	{
		if (++(d->num_philo_finished) >= d->num_philo)
			game_over(d);
	}
	return (NULL);
}

static void game_over(t_data *d)
{
	pthread_mutex_lock(&d->can_set_game_over);
	d->game_over = 1;
	pthread_mutex_unlock(&d->can_set_game_over);
}

static void	*routine(void *arg)
{
	t_philo		*philo;
	t_data		*d;
	uint64_t	bedtime;
	int32_t		num_meals;

	philo = (t_philo *)arg;
	d = philo->data;
	bedtime = get_time(d->start_time);
	num_meals = 0;
	if (philo->status == THINKING)
	{
		print_state(d, philo->id, "is thinking");
		usleep(d->time_to_eat * 1000);
	}
	while (1)
	{
		pthread_mutex_lock(&d->can_set_game_over);
		if (d->game_over == 1)
			break;
		pthread_mutex_unlock(&d->can_set_game_over);
		pthread_mutex_lock(&d->can_eat);
		if (philo->next->status != EATING || philo->prev->status != EATING)
		{
			//////////////////////////////philo_eat
			if (get_time(d->start_time) - bedtime > d->time_to_die)
			{
				philo->status = DEAD;
				pthread_mutex_unlock(&d->can_eat);
				break ;
			}
			else if (d->max_meals >= 0 && num_meals >= d->max_meals)
			{
				philo->status = FINISHED;
				pthread_mutex_unlock(&d->can_eat);
				break ;
			}
			pthread_create(&philo->thread2_id, NULL, &check_death, philo);
			philo->status = EATING;
			pthread_mutex_unlock(&d->can_eat);
			print_state(d, philo->id, "has taken a fork");
			print_state(d, philo->id, "has taken a fork");
			print_state(d, philo->id, "is eating");
			num_meals++;
			usleep(d->time_to_eat * 1000);
			////////////////////////////////////////philo_sleep
			philo->status = SLEEPING;
			print_state(d, philo->id, "is sleeping");
			bedtime = get_time(d->start_time);
			usleep(d->time_to_sleep * 1000);
			//////////philo_think//////////////////
			philo->status = THINKING;
			print_state(d, philo->id, "is thinking");
			//////////////////////////////////
		}
	}
	return (NULL);
}

static void print_state(t_data *d, uint32_t id, char *str)
{
	if (d->game_over != 1)
		printf("%-20lu %-10u %s\n", get_time(d->start_time), id, str);
}

static uint8_t	routine_start(t_philo **table, t_data p)
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

static uint8_t init_table(t_data *d, t_philo **table)
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
			return (write(2, "Error: failed to allocate memory\n", 34) * 0 + 5);
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

static uint8_t	init(t_data *d, char **argv, int8_t is_max_meals)
{
	d->num_philo = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	d->max_meals = -1;
	if (is_max_meals)
		d->max_meals = ft_atoi(argv[5]);
	d->start_time = get_time(0);
	if (pthread_mutex_init(&d->can_eat, NULL) != 0 || pthread_mutex_init(&d->can_set_game_over, NULL) != 0)
		return (write(2, "Error: failed to initialize mutex\n", 35) * 0 + 3);
	d->num_philo_finished = 0;
	d->game_over = 0;
	return (0);
}

static int8_t	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Error: Invalid number of arguments\n", 36) * 0 + 1);
	if (argv[1][0] == '0' || argv[1][0] == '-')
		return (write(2, "Error: Invalid n of philosophers\n", 32) * 0 + 2);
	if (argv[2][0] == '-' || argv[3][0] == '-' || argv[4][0] == '-')
		return (write(2, "Error: Invalid time(s) format\n", 24) * 0 + 3);
	if (argv[5])
	{
		if (argv[5][0] == '0' || argv[5][0] == '-')
			return (write(2, "Invalid number of meals\n", 25) * 0 + 4);
		return (-1);
	}
	return (0);
}


