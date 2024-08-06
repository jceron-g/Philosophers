/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:36:15 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/06 13:38:04 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	aux;

	mutex_handle(mutex, LOCK);
	aux = *value;
	mutex_handle(mutex, UNLOCK);
	return (aux);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	aux;

	mutex_handle(mutex, LOCK);
	aux = *value;
	mutex_handle(mutex, UNLOCK);
	return (aux);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

int	simulation_finished(t_table *table)
{
	return (get_int(&table->mutex_table, &table->end_sim));
}

