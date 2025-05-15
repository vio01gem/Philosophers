/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:47:12 by hajmoham          #+#    #+#             */
/*   Updated: 2025/05/13 15:27:34 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data
{
	unsigned long long	num_philo;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	unsigned long long	time_sleep;
	long long			num_eat;
	int					*forks_array;
	bool				dead;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		die_mutex;
	pthread_mutex_t		print_mutex;
	t_philo				*philo;
}	t_data;

typedef struct s_philo
{
	unsigned long long	philo_id;
	unsigned long long	last_meal;
	unsigned long long	num_eat;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	t_data				*data;
}	t_philo;

// philo_parse.c
int					parse_init(t_data *data, int ac, char **av);
int					check_args(int ac, char **av);

// philo_utils.c
long long			atoi_ll(const	char *str);
unsigned long long	get_time(void);
int					usleep_ms(unsigned long long time, struct s_data *data);

// philo_clean.c
void				putstr(char *str);
void				clean(t_data *data);

// philo_init.c

// phio_data_init.c

// philo_life_cycle.c
void				init_threads(t_data *data);

#endif