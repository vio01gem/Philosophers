/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:52:44 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/20 10:59:06 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//prints a string to the standard output.//
void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

// Cleans up the data structure.//
void	clean(t_data *data)
{
	(void)data;
}
