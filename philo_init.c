#include "philo.h"

int	init_data(t_data *data)
{
	data->forks = malloc(sizeof(int) * data->num_philo);
	if (!data->forks)
		return (putstr("Error: Forks array malloc failed\n"), 1);
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (free(data->forks), putstr("Error: Philos malloc failed\n"), 1);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->fork_mutex)
		return (free(data->forks), free(data->philos),
			putstr("Error: Forks mutex malloc failed\n"), 1);
	data->start_time = get_time();
	return (0);
}

int	init_philos(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philo;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL))
			return (putstr("Error: Forks mutex init failed\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (putstr("Error: Print mutex init failed\n"), 1);
	if (pthread_mutex_init(&data->eat_mutex, NULL))
		return (putstr("Error: Eat mutex init failed\n"), 1);
	if (pthread_mutex_init(&data->die_mutex, NULL))
		return (putstr("Error: Die mutex init failed\n"), 1);
	if (pthread_mutex_init(&data->forks_mutex, NULL))
		return (putstr("Error: Forks array mutex init failed\n"), 1);
	return (0);
}

void	init_forks(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (i == 0 || i == data->num_philo - 1)
			data->forks[i] = data->num_philo; // First/last fork: num_philo
		else if (i % 2 == 0)
			data->forks[i] = i + 2; // Even forks: i + 2
		else
			data->forks[i] = i + 1; // Odd forks: i + 1
		i++;
	}
}

int	create_threads(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
			return (putstr("Error: Thread create failed\n"), 1);
		i++;
	}
	if (data->num_philo > 1 && pthread_create(&data->monitor, NULL,
			monitor_routine, data))
		return (putstr("Error: Monitor create failed\n"), 1);
	if (data->num_philo > 1 && pthread_join(data->monitor, NULL))
		return (putstr("Error: Monitor join failed\n"), 1);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (putstr("Error: Thread join failed\n"), 1);
		i++;
	}
	return (0);
}