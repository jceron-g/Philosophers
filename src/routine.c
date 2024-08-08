/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:16:44 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/08 11:19:17 by jceron-g         ###   ########.fr       */
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
		printf("%ld" "  %d has taken a fork\n", elapsed, philo->id);
	else if (status == EAT && !simulation_finished(philo->table))
		printf("\033[0;34m%ld %d is eating\n\033[0m", elapsed, philo->id);
	else if (status == SLEEP && !simulation_finished(philo->table))
		printf("%ld" "  %d is sleeping\n", elapsed, philo->id);
	else if (status == THINK && !simulation_finished(philo->table))
		printf("%ld" "  %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf("\033[0;31m%ld %d died\n\033[0m", elapsed, philo->id);
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

void	philo_think(t_philo *philo)
{
	print_status(THINK, philo);
}

