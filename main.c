/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:52:39 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/07 10:39:28 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_me(void)
// {
// 	printf("Hello I am philo. Time to eat: time to sleep: time to die: no. of meals\n", );
// }

// Main function to parse arguments and initialize data.//
int	main(int ac, char **av)
{
	t_data	data;

	if (parse(&data, ac, av))
		return (1);
	return (0);
}
