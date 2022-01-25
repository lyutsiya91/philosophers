/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:46:55 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 01:31:00 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clear(t_info *info)
{
	int	i;

	i = 0;
	if (info)
	{
		if (info->philo)
		{
			free(info->philo);
			info->philo = NULL;
		}
		sem_close(info->forks);
		sem_unlink("/forks");
		sem_close(info->print_lock);
		sem_unlink("/print");
		sem_close(info->philo_die);
		sem_unlink("/die");
		sem_close(info->eat_count);
		sem_unlink("/count");
	}
}

int	ft_error(t_info *info)
{
	ft_clear(info);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	die;
	pthread_t	eat;

	memset(&info, 0, sizeof(t_info));
	if (info_init(argc, argv, &info))
		return (ft_error(&info));
	if (table_init(&info))
		return (ft_error(&info));
	if (philos_init(&info))
		return (ft_error(&info));
	if (process_init(&info))
		return (ft_error(&info));
	pthread_create(&die, NULL, philo_die, &info);
	if (argc == 6)
		pthread_create(&eat, NULL, check_number_eat, &info);
	waitpid(-1, NULL, WUNTRACED);
	ft_clear(&info);
	return (0);
}
