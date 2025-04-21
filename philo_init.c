/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:35:25 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/21 10:25:54 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Allocates philos and forks arrays.//
int init_data(t_data *data)
{
    data->philos = malloc(sizeof(t_philo) * data->num_philo);
    if (!data->philos)
        return (putstr("Error: Malloc failed\n"), 1);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
    if (!data->forks)
    {
        free(data->philos);
        return (putstr("Error: Malloc failed\n"), 1);
    }
    data->is_dead = false;
    data->start_time = get_time();
    return (0);
}

// Sets up philosopher structs.//
int init_philos(t_data *data)
{
    unsigned long long i;

    i = 0;
    while (i < data->num_philo)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->num_philo;
        data->philos[i].eat_count = 0;
        data->philos[i].last_eat = data->start_time;
        data->philos[i].data = data;
        i++;
    }
    return (0);
}

// Initializes mutexes for forks, print, and death.//
int init_mutexes(t_data *data)
{
    unsigned long long i;

    i = 0;
    while (i < data->num_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (putstr("Error: Mutex init failed\n"), 1);
        i++;
    }
    if (pthread_mutex_init(&data->print, NULL) || pthread_mutex_init(&data->death, NULL))
        return (putstr("Error: Mutex init failed\n"), 1);
    return (0);
}