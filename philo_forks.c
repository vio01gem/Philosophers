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

// Locks two forks for eating
void	lock_forks(t_philo *philo, int first, int second)
{
	pthread_mutex_lock(&philo->data->fork_mutex[first]); // Lock first fork
	pthread_mutex_lock(&philo->data->fork_mutex[second]); // Lock second fork
}

// Releases two forks after eating
void	release_forks(t_philo *philo, int first, int second)
{
	pthread_mutex_unlock(&philo->data->fork_mutex[first]); // Unlock first fork
	pthread_mutex_unlock(&philo->data->fork_mutex[second]); // Unlock second fork
}