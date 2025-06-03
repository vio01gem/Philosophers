/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:46:29 by hajmoham          #+#    #+#             */
/*   Updated: 2025/06/03 16:46:30 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if a philosopher has died
bool	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->die_mutex);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->die_mutex);
		return (true); // Dead flag is set
	}
	pthread_mutex_unlock(&data->die_mutex);
	return (false);
}

// Checks if all philosophers ate enough
bool	check_eats(t_data *data)
{
	unsigned long long	i;

	if (data->num_eat == -1)
		return (false); // No meal limit
	i = 0;
	while (i < data->num_philo)
	{
		if (data->philos[i].eat_count < (unsigned long long)data->num_eat)
			return (false); // Not all ate enough
		i++;
	}
	return (true); // All ate enough
}

// Marks all philosophers as having concluded their meals
void	meals_end(t_data *data)
{
	pthread_mutex_lock(&data->die_mutex);
	data->dead = true;
	pthread_mutex_unlock(&data->die_mutex);
	pthread_mutex_unlock(&data->eat_mutex);
}

// Marks a philosopher as dead and prints status
void	death_of_philo(t_data *data, unsigned long long i)
{
	pthread_mutex_lock(&data->die_mutex);
	data->dead = true;
	pthread_mutex_unlock(&data->die_mutex);
	print_status(data, data->philos[i].philo_id, DEAD);
	pthread_mutex_unlock(&data->eat_mutex);
}

// Monitors philosophers for death or meal completion
void	*monitor_routine(void *arg)
{
	t_data				*data;
	unsigned long long	i;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->eat_mutex);
			if (data->num_eat > 0 && check_eats(data))
			{
				meals_end(data);
				return (NULL);
			}
			if (get_time() > data->philos[i].last_meal + data->time_die)
			{
				death_of_philo(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat_mutex);
			i++;
		}
	}
	return (NULL);
}
