/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:28:27 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/12 10:50:01 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_number;

	philo_number = philo->table->philo_nbr;
	philo->first_fork = &forks[(pos + 1) % philo_number];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_number];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_eaten = 0;
		philo->table = table;
		mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_sim = 0;
	table->threads_ready = 0;
	table->threads_running_num = 0;
	table->philos = protected_malloc(sizeof(t_philo) * table->philo_nbr);
	mutex_handle(&table->mutex_table, INIT);
	mutex_handle(&table->write_lock, INIT);
	table->forks = protected_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
}
