/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:50:56 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/20 20:13:20 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Validates ac and numeric av.//
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (putstr("Error: Need 4 or 5 args\n"), 1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (!av[i][j])
			return (putstr("Error: Empty arg\n"), 1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (putstr("Error: Non-numeric arg\n"), 1);
			j++;
		}
		if (atoi_ll(av[i]) > INT_MAX || atoi_ll(av[i]) == 0) //check if we need to take care of too big args//
			return (putstr("Error: Arg too big or zero\n"), 1);
		i++;
	}
	return (0);
}

// Stores ac in t_data, checks for zero values.//
int	parse(t_data *data, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	data->num_philo = atoi_ll(av[1]);
	if (data->num_philo > 200)
		return (putstr("Error: Too many philosophers\n"), 1);
	data->time_die = atoi_ll(av[2]);
	data->time_eat = atoi_ll(av[3]);
	data->time_sleep = atoi_ll(av[4]);
	data->num_eat = -1;
	if (ac == 6)
		data->num_eat = atoi_ll(av[5]);
	if (data->num_philo == 0 || data->time_die == 0 || data->time_eat == 0
		|| data->time_sleep == 0 || (ac == 6 && data->num_eat == 0))
		return (putstr("Error: Nothing to do\n"), 1);
	return (0);
}
