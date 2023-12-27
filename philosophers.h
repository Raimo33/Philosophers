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
	DEAD
}						t_status;

typedef enum e_fork_status
{
	USED,
	FREE
}						t_fork_status;

typedef struct s_params
{
	uint32_t	num_philo;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint32_t	num_meals;
}						t_params;

typedef struct s_seat
{
	uint32_t		id;
	uint32_t		meals_eaten;
	t_status		status;
	t_fork_status	fork_status;
	struct s_seat	*next;
}						t_seat;

t_seat	*ft_lstnew(void *content);

#endif