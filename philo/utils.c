/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalio <sgalio@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:44:12 by sgalio            #+#    #+#             */
/*   Updated: 2022/01/23 22:36:25 by sgalio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static int	ft_define_sign(const char *str)
{
	int	sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	return (sign);
}

static long long	ft_convert(const char *str, int sign, long long number)
{
	if (*str && ft_isdigit(*str))
		number = (number * 10) + ((int)*str - '0');
	if ((number - 1 > INT_MAX && sign == -1)
		|| (number > INT_MAX && sign == 1))
		return (-1);
	return (number);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	number;

	sign = 1;
	number = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = ft_define_sign(str);
		str++;
	}
	if (ft_isdigit(*str))
	{
		while (*str && ft_isdigit(*str))
		{
			number = ft_convert(str, sign, number);
			if (number == -1)
				return (0);
			str++;
		}
	}
	return (sign * number);
}
