/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:36:48 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/21 09:42:32 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Philosopher lifecycle: eat, sleep, think.//
void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->data->num_philo == 1)
    {
        usleep_ms(philo->data->time_die);
        return (NULL);
    }
    while (!philo->data->is_dead)
    {
        // Placeholder: add eat, sleep, think later
    }
    return (NULL);
}

// Creates and joins philosopher threads.//
int start_threads(t_data *data)
{
    unsigned long long i;

    i = 0;
    while (i < data->num_philo)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
            return (putstr("Error: Thread create failed\n"), 1);
        i++;
    }
    i = 0;
    while (i < data->num_philo)
    {
        if (pthread_join(data->philos[i].thread, NULL))
            return (putstr("Error: Thread join failed\n"), 1);
        i++;
    }
    return (0);
}