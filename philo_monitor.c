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
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philos[i].eat_count < (unsigned long long)data->num_eat)
		{
			pthread_mutex_unlock(&data->eat_mutex);
			return (false); // Not all ate enough
		}
		pthread_mutex_unlock(&data->eat_mutex);
		i++;
	}
	return (true); // All ate enough
}

// Monitors philosophers for death or meal completion
void	*monitor_routine(void *arg)
{
	t_data				*data;
	unsigned long long	i;

	data = (t_data *)arg;
	// usleep(1000); // Delay to let philosophers start
	while (!is_dead(data))
	{
		if (check_eats(data))
		{
			pthread_mutex_lock(&data->die_mutex);
			data->dead = true; // Stop simulation
			pthread_mutex_unlock(&data->die_mutex);
			return (NULL);
		}
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->eat_mutex);

			printf("%llu\n", get_time() - (data->philos[i].last_meal + data->time_die));
			if (get_time() > data->philos[i].last_meal + data->time_die)
			{
				pthread_mutex_lock(&data->die_mutex);
				data->dead = true; // Set dead flag
				pthread_mutex_unlock(&data->die_mutex);
				print_status(data, data->philos[i].philo_id, DEAD);
				pthread_mutex_unlock(&data->eat_mutex);
				return (NULL); // Stop monitoring
			}
			pthread_mutex_unlock(&data->eat_mutex);
			i++;
		}
		// usleep(1000); // Prevent busy-waiting
	}
	return (NULL);
}
