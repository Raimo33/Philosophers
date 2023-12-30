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

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FINISHED
}						t_status;

typedef enum e_fork_status
{
	USED,
	FREE
}						t_fork;

typedef struct s_data
{
	uint32_t		num_philo;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	int32_t			max_meals;
	uint64_t		start_time;
	uint8_t			game_over;
	uint32_t		num_philo_finished;
	pthread_mutex_t	game_over_mutex;
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	finished_mutex;
}						t_data;

typedef struct s_philo
{
	uint32_t		id;
	int32_t			meals_eaten;
	uint64_t		meal_time;
	t_status		status;
	t_fork			fork;
	pthread_mutex_t	fork_mutex;
	pthread_t		thread_id;
	pthread_t		thread2_id;
	t_data			*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}						t_philo;

int8_t 		routine_start(t_philo **table, t_data p);
void 		handle_lone_philo(t_data d);
uint8_t		is_game_over(t_data *d);
void 		set_game_over(t_data *d);
void 		print_state(t_data *d, uint32_t id, char *str);
int 		ft_atoi(char *nptr);
uint64_t	get_time(uint64_t start);
void		destroy_and_free(t_data *data, t_philo **table);
t_philo		*lst_new(uint32_t i, t_data *d);
void		lst_clear(t_philo **table, t_data d);

#endif