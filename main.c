/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:52:39 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/13 15:46:09 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Main function to parse arguments and initialize data.//
int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (1);
	if (parse_init(&data, ac, av))
		return (1);
	if (data.num_eat == 0)
		return (0);
	//if initialization passes return (1)
	//
	return (0);
}
