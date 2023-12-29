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
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	game_over_mutex;
	pthread_mutex_t	bedtime_mutex;
	pthread_mutex_t	finished_mutex;
}						t_data;

typedef struct s_philo
{
	uint32_t		id;
	int32_t			meals_eaten;
	uint64_t		bedtime;
	t_status		status;
	pthread_t		thread_id;
	pthread_t		thread2_id;
	t_data			*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}						t_philo;

t_philo		*lst_new(uint32_t i, t_data *d);
int 		ft_atoi(char *nptr);
uint64_t	get_time(uint64_t start);

#endif