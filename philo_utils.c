/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:52:51 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/10 21:10:19 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Converts a string to a long long integer.//
long long	atoi_ll(const char *str)
{
	long long	num;

	num = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

// Gets the current time in milliseconds.//
unsigned long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Sleeps for a specified time in milliseconds.//
int	usleep_ms(unsigned long long time, t_philo *philo)
{
	unsigned long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (get_time() - philo->last_meal >= philo->data->time_die) //The philo ashould die whithin the death range
			return(0);
		usleep(500);
	}
	return (1);
}
