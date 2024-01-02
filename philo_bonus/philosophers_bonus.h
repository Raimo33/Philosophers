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

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_data
{
	sem_t				*forks_pool;
	sem_t				*print_sem;
	uint64_t			start_time;
	uint32_t			num_philo;
	uint32_t			time_to_die;
	uint32_t			time_to_eat;
	uint32_t			time_to_sleep;
	int32_t				max_meals;
	struct s_philo		**table;
}						t_data;

typedef struct s_philo
{
	t_data			*data;
	sem_t			*meal_time_sem;
	pid_t			process_id;
	pthread_t		thread_id;
	uint64_t		meal_time;
	uint32_t		id;
	int32_t			meals_eaten;
	struct s_philo	*prev;
	struct s_philo	*next;
	uint8_t			stop;
}						t_philo;

int8_t		routine_start(t_philo **table, t_data d);
void		handle_lone_philo(t_data d);
void		print_state(t_data *d, uint32_t id, char *str);
t_philo		*lst_new(uint32_t i, t_data *d);
void		lst_clear(t_philo **table, t_data d);
int			ft_atoi(char *nptr);
uint64_t	get_time(uint64_t start);
void		destroy_and_free(t_data *data);

#endif