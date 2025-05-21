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

// Monitors philosophers for death
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
		usleep(1000); // Prevent busy-waiting
	}
	return (NULL);
}