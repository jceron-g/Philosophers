/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:02:31 by jceron-g          #+#    #+#             */
/*   Updated: 2024/07/10 16:34:06 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../lib/libft/libft.h"

typedef struct s_fork
{
	pthread_mutex_t	fork;
	pthread_mutex_t fork_id;
}				t_fork;

// Aqui va lo que vamos a pasar por argumentos

typedef struct s_philo
{
	int	id;
	long		meals_eaten;
	long		last_meal; // time passed from last meal
	bool		full;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	thread_id; // a philo is a thread
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_limit_meals;
	long	start_sim;
	bool	end_sim; // When a philo dies or all philos are full
	t_fork	*forks; // array to forks
	t_philo *philos; // array of philos
}				t_table;


/*---------------PARSE----------------*/
void	print_error(char *message);

#endif