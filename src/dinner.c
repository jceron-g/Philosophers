/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:28:39 by jceron-g          #+#    #+#             */
/*   Updated: 2024/07/13 23:32:24 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*En este modulo estara toda la simulacion
0) Si no hay comidas return
0.1) Si solo hay un philo -> hay que hacer una funcion
1) Crear todos los hilos y filos
2) Crear un hilo de monitorizacion para ver que filos estan muertos
3) Sincronizar el principio de la simulacion porque
cada vez que haces:
pthread_create -> philo start running
todos los philo empiezan simultaneamente
4) Unirlo todo.
*/
void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_limit_meals == 0)
		return ; //vuelta al main y limpiamos
	else if (table->philo_nbr == 1)
		;
		// tenemos que crear esto
	else
	{
		while(++i < table->philo_nbr)
			thread_handle(&table->philos[i].thread_id, dinner_sim, &table->philos[i], CREATE);
	}
}
/*Despues de la funcion de arriba podemos decir
que todos los hilos han sido creados asi que podemos 
setear el booleano de threads_ready en true. */
