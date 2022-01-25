/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:46:49 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/24 14:03:38 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	spend_time(int time, int alive)
{
	long	now;

	now = get_time();
	while (get_time() < now + time)
	{
		if (!alive)
			break ;
		usleep(time);
	}
}
