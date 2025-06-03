#include "philo.h"

// Makes philosopher eat, updates forks
int	philo_eat(t_philo *philo)
{
	int	first;
	int	second;

	lock_order(philo, &first, &second);
	if (print_status(philo->shared_data, philo->philo_id, FORK))
		return (release_forks(philo, first, second), 1);
	if (print_status(philo->shared_data, philo->philo_id, FORK))
		return (release_forks(philo, first, second), 1);
	if (print_status(philo->shared_data, philo->philo_id, EAT))
		return (release_forks(philo, first, second), 1);
	if (usleep_ms(philo->shared_data->time_eat, philo))
		return (release_forks(philo, first, second), 1);
	pthread_mutex_lock(&philo->shared_data->eat_mutex);
	philo->last_meal = get_time(); // Update last meal time
	philo->eat_count++; // Increment meal count
	pthread_mutex_unlock(&philo->shared_data->eat_mutex);
	philo->shared_data->forks[first] = philo->philo_id; // Tag forks
	philo->shared_data->forks[second] = philo->philo_id;
	release_forks(philo, first, second);
	return (0); // Eating succeeded
}

// Makes philosopher sleep
int	philo_sleep(t_philo *philo)
{
	if (print_status(philo->shared_data, philo->philo_id, SLEEP))
		return (1); // Stop if dead
	if (usleep_ms(philo->shared_data->time_sleep, philo))
		return (1); // Stop if died during sleep
	return (0);
}

// Makes philosopher think
int	philo_think(t_philo *philo)
{
	if (print_status(philo->shared_data, philo->philo_id, THINK))
		return (1); // Stop if dead
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		first;
	int		second;

	philo = (t_philo *)arg;
	while (!is_dead(philo->shared_data))
	{
		lock_order(philo, &first, &second);
		if (fork_checker(philo, first, second))
		{
			lock_forks(philo, first, second);
			if (philo_eat(philo)) // Eat if forks free
				return (NULL); // Stop if dead
			if (philo_sleep(philo))
				return (NULL);
			if (philo_think(philo)) // Think before eating
				return (NULL);
		}
	}
	return (NULL);
}
