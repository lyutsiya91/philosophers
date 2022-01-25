/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:41:20 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 01:44:07 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_number_eat(void *arg)
{
	t_info	*info;
	int		i;

	pthread_detach(arg);
	info = (t_info *)arg;
	i = 0;
	while (i < info->number_ph)
	{
		sem_wait(info->eat_count);
		i++;
	}
	sem_post(info->philo_die);
	return (NULL);
}

void	*philo_die(void *arg)
{
	t_info	*info;
	int		i;

	pthread_detach(arg);
	info = (t_info *)arg;
	i = 0;
	sem_wait(info->philo_die);
	info->not_dead = 0;
	while (i < info->number_ph)
	{
		info->philo[i].alive = 0;
		i++;
	}
	i = 0;
	while (i < info->number_ph)
	{
		kill(info->philo[i].pid, SIGKILL);
		i++;
	}
	sem_post(info->print_lock);
	return (NULL);
}

void	*philo_control(void *arg)
{
	t_philo	*philo;

	pthread_detach(arg);
	philo = (t_philo *)arg;
	while (philo->info->not_dead && philo->alive)
	{
		if (get_time() - philo->last_eat > philo->info->time_to_die)
		{
			philo->alive = 0;
			sem_wait(philo->info->print_lock);
			printf("%ld %d died\nThe simulation stops!\n", \
				get_time() - philo->info->start, philo->id + 1);
			sem_post(philo->info->philo_die);
		}
		usleep(100);
	}
	return (NULL);
}
