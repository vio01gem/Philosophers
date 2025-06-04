/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:46:59 by hajmoham          #+#    #+#             */
/*   Updated: 2025/06/04 09:34:54 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Validates ac and numeric av
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (putstr("Error: only 4 or 5 args\n"), 1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (!av[i][j])
			return (putstr("Error: give a value\n"), 1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (putstr("Error: only positive numbers\n"), 1);
			j++;
		}
		if (atoi_ll(av[i]) > INT_MAX || atoi_ll(av[i]) < INT_MIN)
			return (putstr("Error: Over your limits! too big\n"), 1);
		i++;
	}
	return (0);
}

// Parses arguments and stores in t_data
int	parse(t_data *data, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	data->num_philo = atoi_ll(av[1]);
	if (data->num_philo > 1000) //check how many philosophers the program can handle
		return (putstr("Error: too many philosophers (-_-) ! \n"), 1);
	data->time_die = atoi_ll(av[2]);
	data->time_eat = atoi_ll(av[3]);
	data->time_sleep = atoi_ll(av[4]);
	data->num_eat = -1;
	if (ac == 6)
		data->num_eat = atoi_ll(av[5]);
	if (data->num_philo == 0 || data->time_die == 0 || data->time_eat == 0
		|| data->time_sleep == 0 || (ac == 6 && data->num_eat == 0))
		return (putstr("Error: raise the numbers a bit\n"), 1);
	data->dead = false;
	return (0);
}
