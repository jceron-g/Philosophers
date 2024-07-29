/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:02:31 by jceron-g          #+#    #+#             */
/*   Updated: 2024/07/13 21:52:46 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/wait.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int 			fork_id;
}				t_fork;

// Aqui va lo que vamos a pasar por argumentos

typedef struct s_philo
{
	int			id;
	long		meals_eaten;
	long		last_meal; // time passed from last meal
	bool		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; // a philo is a thread
	t_table		*table;
}				t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_limit_meals;
	long			start_sim;
	bool			end_sim; // When a philo dies or all philos are full
	bool			threads_ready; // Lo necesitamos para sincronizar los philo
	pthread_mutex_t	mutex_table; // Lo necesiamos para evitar data races mientras leemos la mesa
	t_fork			*forks; // array to forks
	t_philo 		*philos; // array of philos
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

/*------------------PARSE-------------------*/
void	print_error(char *message);
void	parse_input(t_table *table, char **argv);
/*------------------TOOLS-------------------*/
void	ft_putstr_fd(char *s, int fd);
long	ft_atol(char *str);
/*---------------SAFE_FUNCTIONS----------------*/
void	*protected_malloc(size_t bytes);
void	mutex_handle(pthread_mutex_t *mutex, t_mcode mcode);
void	thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_mcode mcode);
/*------------------INIT-------------------*/
void	data_init(t_table *table);

#endif