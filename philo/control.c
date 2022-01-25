/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:41:20 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/23 22:39:08 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_number_eat(t_philo *philo)
{
	int	i;
	int	count;
	int	check;

	while (!philo->info->eat_stop && philo->info->number_eat != -1)
	{
		check = 0;
		i = 0;
		while (i < philo->info->number_ph)
		{
			count = philo->number_eat;
			if (count > philo->info->number_eat)
				check++;
			i++;
		}
		if (check == philo->info->number_ph)
			philo->info->eat_stop = 1;
	}
}

void	philo_die(t_philo *philo, int n, long death_time)
{
	int		i;

	i = 0;
	while (i < philo->info->number_ph)
	{
		philo[i].alive = 0;
		i++;
	}
	pthread_mutex_lock(philo->print_lock);
	if (philo->info->eat_stop == 0)
		printf("%ld %d died\nThe simulation stops!\n", \
			death_time - philo->info->start, philo[n].id + 1);
	else
		printf("The simulation stops!\n");
	pthread_mutex_unlock(philo->print_lock);
}

void	*philo_control(void *arg)
{
	t_philo	*philo;
	long	death_time;
	int		i;

	philo = (t_philo *)arg;
	while (philo->info->not_dead)
	{
		i = 0;
		while (i < philo->info->number_ph)
		{
			check_number_eat(philo);
			if (philo->info->eat_stop
				|| get_time() - philo[i].last_eat > philo->info->time_to_die)
			{
				philo[i].alive = 0;
				philo->info->not_dead = 0;
				death_time = get_time();
				break ;
			}
			i++;
		}
	}
	philo_die(philo, i, death_time);
	return (NULL);
}
