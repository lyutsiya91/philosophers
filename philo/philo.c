/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:46:55 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 18:36:35 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear(t_info *info)
{
	int	i;

	i = 0;
	if (info->forks)
	{
		while (i < info->number_ph)
		{
			pthread_mutex_destroy(&(info->forks[i]));
			i++;
		}
		free(info->forks);
		info->forks = NULL;
	}
	if (info->philo->t)
	{
		free(info->philo->t);
		info->philo->t = NULL;
	}
	if (info->philo)
	{
		free(info->philo);
		info->philo = NULL;
	}
	pthread_mutex_destroy(&info->print_lock);
}

int	ft_error(t_info *info)
{
	ft_clear(info);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (info_init(argc, argv, &info))
		return (1);
	if (table_init(&info))
		return (ft_error(&info));
	if (philos_init(&info))
		return (ft_error(&info));
	if (threads_init(&info))
		return (ft_error(&info));
	ft_clear(&info);
	return (0);
}
