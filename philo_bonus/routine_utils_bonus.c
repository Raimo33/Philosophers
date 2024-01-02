/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:21:57 by craimond          #+#    #+#             */
/*   Updated: 2024/01/02 17:11:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void print_state(t_data *d, uint32_t id, char *str)
{
	sem_wait(d->print_sem);
	printf("%-20lu %-10u %s\n", get_time(d->start_time), id, str);
	sem_post(d->print_sem);
}
