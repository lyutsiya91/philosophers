/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:34:38 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 01:58:26 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, S_IRWXU, info->number_ph);
	if (info->forks == SEM_FAILED)
		return (printf("Error of creating semaphore!\n"));
	sem_unlink("/print");
	info->print_lock = sem_open("/print", O_CREAT, S_IRWXU, 1);
	if (info->print_lock == SEM_FAILED)
		return (printf("Error of creating semaphore!\n"));
	sem_unlink("/die");
	info->philo_die = sem_open("/die", O_CREAT, S_IRWXU, 0);
	if (info->philo_die == SEM_FAILED)
		return (printf("Error of creating semaphore!\n"));
	sem_unlink("/count");
	info->eat_count = sem_open("/count", O_CREAT, S_IRWXU, 0);
	if (info->eat_count == SEM_FAILED)
		return (printf("Error of creating semaphore!\n"));
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
		info->philo[i].info = info;
		i++;
	}
	return (0);
}

int	process_init(t_info *info)
{
	int	i;

	i = 0;
	info->start = get_time();
	while (i < info->number_ph)
	{
		info->philo[i].pid = fork();
		if (info->philo[i].pid == -1)
			return (printf("Error of creating fork!\n"));
		if (info->philo[i].pid == 0)
			philo_life(&(info->philo[i]));
		i++;
		usleep(100);
	}
	return (0);
}
