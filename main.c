/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:45:50 by hajmoham          #+#    #+#             */
/*   Updated: 2025/06/04 10:30:03 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parse(&data, ac, av))
		return (1);
	if (data.num_eat == 0)
		return (0);
	if (init_data(&data) || init_philos(&data) || init_mutex(&data))
		return (clean(&data), 1);
	init_forks(&data);
	if (create_threads(&data))
		return (clean(&data), 1);
	usleep(1000); // Ensure threads finish
	clean(&data);
	return (0);
}
