/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:47:14 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 19:20:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_data
{
	pthread_mutex_t	game_over_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	print_mutex;
	uint64_t		start_time;
	uint32_t		num_philo;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	int32_t			max_meals;
	uint32_t		num_philo_finished;
	uint8_t			game_over;
}						t_data;

typedef struct s_philo
{
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	meal_time_mutex;
	pthread_t		thread_id;
	pthread_t		thread2_id;
	t_data			*data;
	uint64_t		meal_time;
	uint32_t		id;
	int32_t			meals_eaten;
	struct s_philo	*prev;
	struct s_philo	*next;
	uint8_t			stop;
}						t_philo;

int8_t		routine_start(t_philo **table, t_data p);
void		handle_lone_philo(t_data d);
uint8_t		is_game_over(t_data *d);
void		set_game_over(t_data *d);
void		print_state(t_data *d, uint32_t id, char *str);
int			ft_atoi(char *nptr);
uint64_t	get_time(uint64_t start);
void		destroy_and_free(t_data *data, t_philo **table);
t_philo		*lst_new(uint32_t i, t_data *d);
void		lst_clear(t_philo **table, t_data d);

#endif