/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:59:30 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 01:30:45 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	int		number_ph;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_eat;
	long	start;
	int		not_dead;
	int		eat_stop;
	sem_t	*forks;
	sem_t	*print_lock;
	sem_t	*philo_die;
	sem_t	*eat_count;
	t_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int		id;
	int		alive;
	int		number_eat;
	long	last_eat;
	pid_t	pid;
	t_info	*info;
}	t_philo;

int		info_init(int argc, char **argv, t_info *info);
int		table_init(t_info *info);
int		philos_init(t_info *info);
int		process_init(t_info *info);
void	*philo_life(void *arg);
void	philo_take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*philo_control(void *arg);
void	*philo_die(void *arg);
void	*check_number_eat(void *arg);
long	get_time(void);
void	spend_time(int time, int alive);
int		ft_atoi(const char *str);

#endif
