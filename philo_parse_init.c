/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:50:56 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/13 15:39:45 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Validates ac and numeric av.//
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (putstr("Error: I only take 4 or 5 args\n"), 1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (!av[i][j])
			return (putstr("Error: I feel empty\n"), 1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (putstr("Error: These aint Numbers.. I am told to take in only numbers\n"), 1);
			j++;
		}
		if (atoi_ll(av[i]) > INT_MAX) //check if we need to take care of too big args//
			return (putstr("Error: Over your limits now! too big\n"), 1);
		i++;
	}
	return (0);
}

// This function parses the arguments and initializes the some of the data structure.//
int	parse_init(t_data *data, int ac, char **av)
{
	data->num_philo = atoi_ll(av[1]);
	// if (data->num_philo > 200) //check what the max number of philosophers the project is able to handle, your not suppose to know this number//
	// 	return (putstr("Error: Hold you horses.. thats too many philosophers now\n"), 1);
	data->time_die = atoi_ll(av[2]);
	data->time_eat = atoi_ll(av[3]);
	data->time_sleep = atoi_ll(av[4]);
	data->num_eat = -1;
	if (ac == 6)
		data->num_eat = atoi_ll(av[5]);
	if (data->num_philo == 0 || data->time_die == 0 || data->time_eat == 0
		|| data->time_sleep == 0 || (ac == 6 && data->num_eat == 0))
		return (putstr("Error: bruhh.. nothing much to do.. maybe raise the numbers a bit\n"), 1);
	data->dead = false;
	data->forks_array = malloc(sizeof(int) * data->num_philo);
	if (!data->forks_array)
		return (putstr("Error: Forks array malloc failed\n"), 1);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (free(data->forks_array), putstr("Philo Malloc failed\n"), 1);
}

int mutex_init(t_data *data)
{
	int	i;

	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks_mutex)
		return (putstr("Error: Forks mutex malloc failed\n"), 1);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks_mutex[i], NULL))
			return (putstr("Error: Forks mutex init failed\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&data->eat_mutex, NULL))
		return (putstr("Error: Eat mutex init failed\n"), 1);
	if (pthread_mutex_init(&data->die_mutex, NULL))
		return (putstr("Error: Die mutex init failed\n"), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (putstr("Error: Print mutex init failed\n"), 1);
	return (0);
}