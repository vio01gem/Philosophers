/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:52:51 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/19 13:58:27 by hajmoham         ###   ########.fr       */
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
int	usleep_ms(unsigned long long time)
{
	unsigned long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
	return (0);
}
