/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:34:38 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 18:03:08 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	info_init(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: invalid number of arguments!\n"));
	info->number_ph = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_eat = ft_atoi(argv[5]);
	else
		info->number_eat = -1;
	if (info->time_to_die <= 0 || info->time_to_eat <= 0
		|| info->time_to_sleep <= 0 || info->number_ph <= 0)
		return (printf("Error: invalid argument(s)!\n"));
	if (argc == 6 && info->number_eat <= 0)
		return (printf("Error: invalid argument(s)!\n"));
	info->not_dead = 1;
	info->eat_stop = 0;
	return (0);
}

int	table_init(t_info *info)
{
	int	i;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* info->number_ph);
	if (!info->forks)
		return (printf("Error of allocating memory!\n"));
	i = 0;
	while (i < info->number_ph)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&info->print_lock, NULL);
	return (0);
}

int	philos_init(t_info *info)
{
	int		i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number_ph);
	if (!info->philo)
		return (printf("Error of allocating memory!\n"));
	i = 0;
	info->start = get_time();
	while (i < info->number_ph)
	{
		info->philo[i].id = i;
		info->philo[i].alive = 1;
		info->philo[i].number_eat = 0;
		info->philo[i].last_eat = info->start;
		info->philo[i].left_fork = &(info->forks[i]);
		info->philo[i].right_fork = &(info->forks[(i + 1) % info->number_ph]);
		info->philo[i].print_lock = &(info->print_lock);
		info->philo[i].info = info;
		i++;
	}
	return (0);
}

int	threads_init(t_info *info)
{
	pthread_t	control;
	int			i;

	info->philo->t = (pthread_t *)malloc(sizeof(pthread_t) * info->number_ph);
	if (!info->philo->t)
		return (printf("Error of allocating memory!\n"));
	i = 0;
	while (i < info->number_ph)
	{
		pthread_create(&info->philo->t[i], NULL, philo_life, &info->philo[i]);
		i += 2;
	}
	usleep(info->time_to_eat);
	i = 1;
	while (i < info->number_ph)
	{
		pthread_create(&info->philo->t[i], NULL, philo_life, &info->philo[i]);
		i += 2;
	}
	pthread_create(&control, NULL, philo_control, info->philo);
	pthread_join(control, NULL);
	return (0);
}
