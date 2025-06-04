/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:46:04 by hajmoham          #+#    #+#             */
/*   Updated: 2025/06/04 10:02:07 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Cleans up resources used by the simulation
void	clean(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->die_mutex);
	free(data->fork_mutex);
	free(data->philos);
	free(data->forks);
}
