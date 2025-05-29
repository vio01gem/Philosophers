#include "philo.h"

// Sets fork lock order to avoid deadlocks
void	lock_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork; // Lower index first
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork; // Lower index first
		*second = philo->left_fork;
	}
}

// Checks if forks are free for philosopher
int	fork_checker(t_philo *philo, int first, int second)
{
	int	first_id;
	int	second_id;

	pthread_mutex_lock(&philo->shared_data->fork_mutex[first]);
	first_id = philo->shared_data->forks[first];
	pthread_mutex_unlock(&philo->shared_data->fork_mutex[first]);
	pthread_mutex_lock(&philo->shared_data->fork_mutex[second]); // Get first fork's tag
	second_id = philo->shared_data->forks[second];
	pthread_mutex_unlock(&philo->shared_data->fork_mutex[second]); // Get second fork's tag
	if (first_id != (int)philo->philo_id && second_id != (int)philo->philo_id)
		return (1); // Forks are free
	return (0);
}

// Locks two forks for eating
void	lock_forks(t_philo *philo, int first, int second)
{
	lock_order(philo, &first, &second);
	pthread_mutex_lock(&philo->shared_data->fork_mutex[first]); // Lock first fork
	pthread_mutex_lock(&philo->shared_data->fork_mutex[second]); // Lock second fork
}

// Releases two forks after eating
void	release_forks(t_philo *philo, int first, int second)
{
	lock_order(philo, &first, &second);
	pthread_mutex_unlock(&philo->shared_data->fork_mutex[first]); // Unlock first fork
	pthread_mutex_unlock(&philo->shared_data->fork_mutex[second]); // Unlock second fork
}