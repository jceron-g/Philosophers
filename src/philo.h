/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:02:31 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/08 15:30:17 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

// Aqui va lo que vamos a pasar por argumentos

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal_time; // time passed from last meal
	int				full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id; // a philo is a thread
	t_table			*table;
	pthread_mutex_t	philo_mutex; //useful for races with the monitor
}				t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_limit_meals;
	long			start_sim;
	int				end_sim; // When a philo dies or all philos are full
	int				threads_ready; // Lo necesitamos para sincronizar los philo
	long			threads_running_num;
	pthread_mutex_t	mutex_table; // Lo necesitamos para evitar data races mientras leemos la mesa
	pthread_mutex_t	write_lock; // Va a ser nuestro mutex para poder ir escribiendo
	pthread_t		monitor_thread; // va a ser el hilo que nos sirva para monitorear nuestros filosofos
	t_fork			*forks; // array to forks
	t_philo			*philos; // array of philos
};

typedef enum e_mcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_mcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}			t_time_code;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}			t_status;

/*---------------------PARSE----------------------*/
void	print_error(char *message);
void	parse_input(t_table *table, char **argv);
/*---------------------TOOLS----------------------*/
void	ft_putstr_fd(char *s, int fd);
long	ft_atol(char *str);
long	get_time(t_time_code time_code);
void	ft_usleep(long usec, t_table *table);
void	print_status(t_status status, t_philo *philo);
/*----------------SAFE_FUNCTIONS----------------*/
void	*protected_malloc(size_t bytes);
void	mutex_handle(pthread_mutex_t *mutex, t_mcode mcode);
void	thread_handle(pthread_t *thread,
			void *(*foo)(void *), void *data, t_mcode mcode);
/*------------------INIT------------------------*/
void	data_init(t_table *table);
/*-----------------GET AND SET------------------*/
void	set_int(pthread_mutex_t *mutex, int *dest, int value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
int		get_int(pthread_mutex_t *mutex, int *value);
long	get_long(pthread_mutex_t *mutex, long *value);
int		simulation_finished(t_table *table);
/*-----------------SYNCHRO-UTILS------------------*/
void	wait_threads(t_table *table);
void	increase_thread_num(pthread_mutex_t *mutex, long *value);

/*-----------------ROUTINE------------------*/
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
/*-----------------SIMULATION------------------*/
void	*dinner_sim(void *data);
void	dinner_start(t_table *table);
/*-----------------MONITORING------------------*/
void	*monitor(void *data);
#endif