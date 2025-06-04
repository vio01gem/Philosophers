/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:42:44 by hajmoham          #+#    #+#             */
/*   Updated: 2025/06/04 09:43:26 by hajmoham         ###   ########.fr       */
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

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

typedef struct s_philo
{
	unsigned long long	philo_id;	 // Philosopher ID
	unsigned long long	last_meal;	 // Time of last meal (ms)
	unsigned long long	eat_count; 	 // Number of meals eaten
	int					left_fork; 	 // Index of left fork
	int					right_fork;  // Index of right fork
	pthread_t			thread;		 // Thread for this philosopher
	struct s_data		*shared_data;// Pointer to shared data
}						t_philo;

typedef struct s_data
{
	unsigned long long	num_philo;	// Number of philosophers
	unsigned long long	time_die;	// Time to die (ms)
	unsigned long long	time_eat;	// Time to eat (ms)
	unsigned long long	time_sleep;	// Time to sleep (ms)
	unsigned long long	start_time;	// Simulation start time (ms)
	pthread_mutex_t		*fork_mutex;// Mutexes for forks
	pthread_mutex_t		print_mutex;// Mutex for printing
	pthread_mutex_t		eat_mutex;	// Mutex for eat_count/last_meal
	pthread_mutex_t		die_mutex;	// Mutex for dead flag
	pthread_t			monitor;	// Monitor thread
	long long			num_eat;	// Number of meals (optional, -1 if none)
	int					*forks;		// Fork status array
	bool				dead;		// True if a philosopher dies
	t_philo				*philos;	// Array of philosophers
}						t_data;

// philo_parse.c
int						check_args(int ac, char **av);
int						parse(t_data *data, int ac, char **av);

// philo_utils.c
long long				atoi_ll(const char *str);
unsigned long long		get_time(void);
int						usleep_ms(unsigned long long time, t_philo *philo);
void					putstr(char *str);
int						print_status(t_data *data, int id, int status);

// philo_clean.c
void					clean(t_data *data);

// philo_init.c
int						init_data(t_data *data);
int						init_philos(t_data *data);
int						init_mutex(t_data *data);
void					init_forks(t_data *data);
int						create_threads(t_data *data);

// philo_cycle.c
int						philo_eat(t_philo *philo);
int						philo_sleep(t_philo *philo);
int						philo_think(t_philo *philo);
void					one_philo_case(t_philo *philo);
void					*philo_routine(void *arg);

// philo_monitor.c
bool					is_dead(t_data *data);
bool					check_eats(t_data *data);
void					meals_end(t_data *data);
void					death_of_philo(t_data *data, unsigned long long i);
void					*monitor_routine(void *arg);

// philo_forks.c
void					lock_order(t_philo *philo, int *first, int *second);
int						fork_checker(t_philo *philo, int first, int second);
void					lock_forks(t_philo *philo, int first, int second);
void					release_forks(t_philo *philo, int first, int second);

#endif
