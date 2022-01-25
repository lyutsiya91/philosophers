/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:32:45 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 01:32:00 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_think(t_philo *philo)
{
	sem_wait(philo->info->print_lock);
	if (philo->alive && philo->info->not_dead)
		printf("%ld %d is thinking\n", \
			get_time() - philo->info->start, philo->id + 1);
	sem_post(philo->info->print_lock);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->info->print_lock);
	if (philo->alive && philo->info->not_dead)
		printf("%ld %d is sleeping\n", \
			get_time() - philo->info->start, philo->id + 1);
	sem_post(philo->info->print_lock);
	spend_time(philo->info->time_to_sleep, philo->alive);
}		

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->info->print_lock);
	if (philo->alive && philo->info->not_dead)
		printf("%ld %d is eating\n", \
			get_time() - philo->info->start, philo->id + 1);
	sem_post(philo->info->print_lock);
	philo->last_eat = get_time();
	philo->number_eat++;
	spend_time(philo->info->time_to_eat, philo->alive);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	if (philo->number_eat == philo->info->number_eat
		&& philo->info->number_eat > 0)
		sem_post(philo->info->eat_count);
}

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	sem_wait(philo->info->print_lock);
	if (philo->alive && philo->info->not_dead)
		printf("%ld %d has taken a fork\n", \
			get_time() - philo->info->start, philo->id + 1);
	sem_post(philo->info->print_lock);
	sem_wait(philo->info->forks);
	sem_wait(philo->info->print_lock);
	if (philo->alive && philo->info->not_dead)
		printf("%ld %d has taken a fork\n", \
			get_time() - philo->info->start, philo->id + 1);
	sem_post(philo->info->print_lock);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;
	pthread_t	control;

	philo = (t_philo *)arg;
	pthread_create(&control, NULL, philo_control, philo);
	while (philo->alive && philo->info->not_dead)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}		
	return (NULL);
}
