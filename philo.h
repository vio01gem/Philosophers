/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:27:09 by hajmoham          #+#    #+#             */
/*   Updated: 2025/04/21 09:43:43 by hajmoham         ###   ########.fr       */
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
	int					id;
	int					left_fork;
	int					right_fork;
	unsigned long long	eat_count;
	unsigned long long	last_eat;
	pthread_t			thread;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	unsigned long long	num_philo;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	unsigned long long	time_sleep;
	long long           num_eat;
	t_philo             *philos;
	pthread_mutex_t     *forks;
	pthread_mutex_t     print;
	pthread_mutex_t     death;
	bool                is_dead;
	unsigned long long  start_time;
} t_data;

// philo_parse.c
int                 parse(t_data *data, int ac, char **av);
int                 check_args(int ac, char **av);

// philo_utils.c
void                putstr(char *str);
long long           atoi_ll(const char *str);
unsigned long long  get_time(void);
int                 usleep_ms(unsigned long long time);

// philo_clean.c
void                clean(t_data *data);

// philo_init.c
int                 init_data(t_data *data);
int                 init_philos(t_data *data);
int                 init_mutexes(t_data *data);

// philo_threads.c
int start_threads(t_data *data);

#endif