/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:02:18 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/08 15:44:38 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_int(&table->mutex_table, &table->threads_ready))
		;
}

//El monitor espera hasta que los hilos empiezan a funcionar
//Monitor busy waits until all threads are running
// int	threads_running()
// {

// }

//Esta funcion sirve para incrementar el numero de hilos
//para sincronizarlo con el monitor
void	increase_thread_num(pthread_mutex_t *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}
