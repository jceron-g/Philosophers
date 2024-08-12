/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:43:59 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/12 10:50:31 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	elapsed = get_time(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

void	*monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!threads_running(&table->mutex_table,
			&table->threads_running_num, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_dead (table->philos + i))
			{
				set_int(&table->mutex_table, &table->end_sim, 1);
				print_status(DEAD, table->philos + i);
			}
		}
	}
	return (NULL);
}
