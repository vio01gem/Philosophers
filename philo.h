/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:47:12 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/07 10:25:01 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	unsigned long long	philo_id;
}	t_philo;

typedef struct s_data
{
	unsigned long long	num_philo;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	unsigned long long	time_sleep;
	long long			num_eat;
	t_philo			    *philo_info;
}	t_data;

// philo_parse.c
int					parse(t_data *data, int ac, char **av);
int					check_args(int ac, char **av);

// philo_utils.c
long long			atoi_ll(const	char *str);
unsigned long long	get_time(void);
int					usleep_ms(unsigned long long time);

// philo_clean.c
void				putstr(char *str);
void				clean(t_data *data);

#endif