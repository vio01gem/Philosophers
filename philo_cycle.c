#include "philo.h"

// Makes philosopher eat, updates forks
int	philo_eat(t_philo *philo)
{
	int	first;
	int	second;
	int	first_id;
	int	second_id;

	lock_order(philo, &first, &second);
	lock_forks(philo, first, second);
	pthread_mutex_lock(&philo->data->forks_mutex);
	first_id = philo->data->forks[first]; // Get first fork's tag
	second_id = philo->data->forks[second]; // Get second fork's tag
	if (first_id != (int)philo->philo_id && second_id != (int)philo->philo_id)
	{
		pthread_mutex_unlock(&philo->data->forks_mutex);
		if (print_status(philo->data, philo->philo_id, FORK))
			return (release_forks(philo, first, second), 0);
		if (print_status(philo->data, philo->philo_id, FORK))
			return (release_forks(philo, first, second), 0);
		if (print_status(philo->data, philo->philo_id, EAT))
			return (release_forks(philo, first, second), 0);
		if (usleep_ms(philo->data->time_eat, philo))
			return (release_forks(philo, first, second), 0);
		pthread_mutex_lock(&philo->data->eat_mutex);
		philo->last_meal = get_time(); // Update last meal time
		philo->eat_count++; // Increment meal count
		pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_mutex_lock(&philo->data->forks_mutex);
		philo->data->forks[first] = philo->philo_id; // Tag forks
		philo->data->forks[second] = philo->philo_id;
		pthread_mutex_unlock(&philo->data->forks_mutex);
		release_forks(philo, first, second);
		return (1); // Eating succeeded
	}
	pthread_mutex_unlock(&philo->data->forks_mutex);
	release_forks(philo, first, second);
	return (0); // Forks not free
}

// Makes philosopher sleep
int	philo_sleep(t_philo *philo)
{
	if (print_status(philo->data, philo->philo_id, SLEEP))
		return (1); // Stop if dead
	if (usleep_ms(philo->data->time_sleep, philo))
		return (1); // Stop if died during sleep
	return (0);
}

// Makes philosopher think
int	philo_think(t_philo *philo)
{
	if (print_status(philo->data, philo->philo_id, THINK))
		return (1); // Stop if dead
	return (0);
}

// Philosopher's main routine: eat, sleep, think
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo_think(philo)) // Start with thinking
		return (NULL);
	while (!is_dead(philo->data))
	{
		if (philo_eat(philo)) // Eat if forks free
		{
			if (philo_sleep(philo))
				return (NULL); // Stop if dead
			if (philo_think(philo))
				return (NULL); // Stop if dead
		}
		usleep(1000); // Prevent busy-waiting
	}
	return (NULL);
}