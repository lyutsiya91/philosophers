/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:32:45 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 14:58:32 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	if (philo->alive)
		printf("%ld %d is thinking\n", \
			get_time() - philo->info->start, philo->id + 1);
	pthread_mutex_unlock(philo->print_lock);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	if (philo->alive)
		printf("%ld %d is sleeping\n", \
			get_time() - philo->info->start, philo->id + 1);
	pthread_mutex_unlock(philo->print_lock);
	spend_time(philo->info->time_to_sleep, philo->alive);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	if (philo->alive)
		printf("%ld %d is eating\n", \
			get_time() - philo->info->start, philo->id + 1);
	pthread_mutex_unlock(philo->print_lock);
	philo->last_eat = get_time();
	philo->number_eat++;
	spend_time(philo->info->time_to_eat, philo->alive);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->print_lock);
	if (philo->alive)
		printf("%ld %d has taken a fork\n", \
			get_time() - philo->info->start, philo->id + 1);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print_lock);
	if (philo->alive)
		printf("%ld %d has taken a fork\n", \
			get_time() - philo->info->start, philo->id + 1);
	pthread_mutex_unlock(philo->print_lock);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	pthread_detach(arg);
	philo = (t_philo *)arg;
	while (philo->alive)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
