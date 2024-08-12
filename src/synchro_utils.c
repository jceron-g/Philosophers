/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:02:18 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/12 10:49:31 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_int(&table->mutex_table, &table->threads_ready))
		;
}

int	threads_running(pthread_mutex_t *mutex, long *threads, long philo_num)
{
	int	ret;

	ret = 0;
	mutex_handle(mutex, LOCK);
	if (*threads == philo_num)
		ret = 1;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_thread_num(pthread_mutex_t *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}

void	de_synchro_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			philo_think(philo, 1);
	}
}
