/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattif <mattif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 02:59:21 by mattif            #+#    #+#             */
/*   Updated: 2022/06/17 19:21:53 by mattif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(int error)
{
	if (error == 0)
		write (2, "Not Enough Arguments\n", 22);
	if (error == 1)
		write(2, "positive numbers only\n", 23);
	if (error == 2)
		write(2, "Too many arguments\n", 20);
	exit(0);
}

long long	ft_atoi(const char *str)
{
	int				i;
	int				n;
	long long		res;

	i = 0;
	res = 0;
	n = 1;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		||str[i] == '\f' || str[i] == '\v' || str[i] == ' ' )
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * n);
}

int check_death(t_phl *philos, int num)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < num)
		{
			if (philos[i % num].life_time
				< time_passed(philos[i % num].last_meal))
			{
				pthread_mutex_lock(philos[i].print);
				printf("%lld ms philosopher %d died\n",
					time_passed(philos[i % num].start), philos[i % num].id);
				usleep(100);
				return (1);
			}
			i++;
		}
		if (philos->got_num && check_eat(philos, num))
			return (1);
	}
	return (0);
}

