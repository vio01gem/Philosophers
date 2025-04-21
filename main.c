/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:38:34 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/21 10:11:02 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Main function to parse, initialize, and run simulation.//
int main(int ac, char **av)
{
    t_data data;

    if (parse(&data, ac, av))
        return (1);
    if (init_data(&data) || init_philos(&data) || init_mutexes(&data))
        return (clean(&data), 1);
    if (start_threads(&data))
        return (clean(&data), 1);
    clean(&data);
    return (0);
}