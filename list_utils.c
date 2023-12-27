/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:37:38 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 19:43:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_seat	*ft_lstnew(t_params *p, uint32_t i)
{
	t_seat	*new_seat;

	new_seat = malloc(sizeof(t_seat));
	if (!new_seat)
		return (NULL);
	new_seat->id = i;
    new_seat->meals_eaten = 0;
    new_seat->status = THINKING;
    new_seat->fork_status = FREE;
	new_seat->next = NULL;
	return (new_seat);
}
