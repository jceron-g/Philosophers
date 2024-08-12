/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:28:39 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/12 10:49:50 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	increase_thread_num(&philo->table->mutex_table,
		&philo->table->threads_running_num);
	de_synchro_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		philo_eat(philo);
		print_status(SLEEP, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		philo_think(philo, 0);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		thread_handle(&table->philos[0].thread_id,
			one_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			thread_handle(&table->philos[i].thread_id,
				dinner_sim, &table->philos[i], CREATE);
	}
	thread_handle(&table->monitor_thread, monitor, table, CREATE);
	table->start_sim = get_time(MILISECOND);
	set_int(&table->mutex_table, &table->threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_int(&table->mutex_table, &table->end_sim, 1);
	thread_handle(&table->monitor_thread, NULL, NULL, JOIN);
}
