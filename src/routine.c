/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:16:44 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/12 11:23:25 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->table->start_sim;
	mutex_handle(&philo->table->write_lock, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& (!simulation_finished(philo->table)))
		printf("%ld  %d has taken a fork\n", elapsed, philo->id);
	else if (status == EAT && !simulation_finished(philo->table))
		printf("\033[0;33m%ld  %d is eating\n\033[0m", elapsed, philo->id);
	else if (status == SLEEP && !simulation_finished(philo->table))
		printf("\033[0;34m%ld  %d is sleeping\n\033[0m", elapsed, philo->id);
	else if (status == THINK && !simulation_finished(philo->table))
		printf("\033[0;32m%ld  %d is thinking\n\033[0m", elapsed, philo->id);
	else if (status == DEAD)
		printf("\033[0;31m%ld  %d died\n\033[0m", elapsed, philo->id);
	mutex_handle(&philo->table->write_lock, UNLOCK);
}

void	philo_eat(t_philo *philo)
{
	mutex_handle(&philo->first_fork->fork, LOCK);
	print_status(TAKE_FIRST_FORK, philo);
	mutex_handle(&philo->second_fork->fork, LOCK);
	print_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	philo->meals_eaten++;
	print_status(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_limit_meals > 0
		&& philo->meals_eaten == philo->table->num_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 1);
	mutex_handle(&philo->first_fork->fork, UNLOCK);
	mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	philo_think(t_philo *philo, int pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		print_status(THINK, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->table);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	increase_thread_num(&philo->table->mutex_table,
		&philo->table->threads_running_num);
	print_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		ft_usleep(200, philo->table);
	return (NULL);
}
