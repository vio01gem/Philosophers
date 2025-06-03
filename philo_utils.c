/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:47:06 by hajmoham          #+#    #+#             */
/*   Updated: 2025/06/03 16:47:07 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Converts string to long long
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

// Gets current time in milliseconds
unsigned long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Sleeps for time ms, checks for death
int	usleep_ms(unsigned long long time, t_philo *philo)
{
	const unsigned long long	start = get_time();

	int i = 0;
	while (get_time() < (start + time))
	{
		// printf("%llu < %llu: [%i]\n", get_time(), start + time, i);
		if (is_dead(philo->shared_data))
			return (1);
		usleep(500);
		i++;
	}
	// printf("usleep_ms finished after %d iterations\n", i);
	return (0);
}

// Prints string to stdout
void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

// Prints philosopher status with mutex
int	print_status(t_data *data, int id, int status)
{
	pthread_mutex_lock(&data->print_mutex);
	if (status == DEAD)
		printf("%llu %d died\n", get_time() - data->start_time, id);
	if (is_dead(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		return (1); // Stop if dead
	}
	printf("%llu %d ", get_time() - data->start_time, id);
	if (status == EAT)
		printf("is eating\n");
	else if (status == SLEEP)
		printf("is sleeping\n");
	else if (status == THINK)
		printf("is thinking\n");
	else if (status == FORK)
		printf("has taken a fork\n");
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}
