/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:52:39 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/19 13:59:40 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Main function to parse arguments and initialize data.//
int	main(int ac, char **av)
{
	t_data	data;

	if (parse(&data, ac, av))
		return (1);
	return (0);
}
