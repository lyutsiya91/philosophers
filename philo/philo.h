/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:59:30 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/25 01:51:52 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	int				number_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	long			start;
	int				not_dead;
	int				eat_stop;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_info;

typedef struct s_philo
{
	pthread_t		*t;
	int				id;
	int				alive;
	int				number_eat;
	long			last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	t_info			*info;
}	t_philo;

int		info_init(int argc, char **argv, t_info *info);
int		table_init(t_info *info);
int		philos_init(t_info *info);
int		threads_init(t_info *info);
void	*philo_life(void *arg);
void	philo_take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*philo_control(void *arg);
void	philo_die(t_philo *philo, int n, long death_time);
void	check_number_eat(t_philo *philo);
long	get_time(void);
void	spend_time(int time, int alive);
int		ft_atoi(const char *str);

#endif
