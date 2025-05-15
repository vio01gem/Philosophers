/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:56:22 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/13 11:58:08 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function initializes values for the data structure
int data_init(t_data *data, int ac, char **av)
{
    data->num_philo = atoi_ll(av[1]);
    data->time_die = atoi_ll(av[2]);
    data->time_eat = atoi_ll(av[3]);
    data->time_sleep = atoi_ll(av[4]);
    data->num_eat = -1;
    if (ac == 6)
        data->num_eat = atoi_ll(av[5]);
    data->dead = false;
    data->forks_array = NULL;
    data->forks_mutex = NULL;
    pthread_mutex_init(&data->eat_mutex, NULL);
    pthread_mutex_init(&data->die_mutex, NULL);
    return (0);
}
