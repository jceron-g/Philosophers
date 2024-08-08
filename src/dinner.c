/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:28:39 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/08 15:44:12 by jceron-g         ###   ########.fr       */
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
void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	//spinlock wait_threads va a tener la simulacion en bucle hasta que la flag se setea en 1 o true
	wait_threads(philo->table);
	//sincronizamos con el monitor
	//incrementamos un contador de table variable con todos los hilos corriendo
	increase_thread_num(&philo->table->mutex_table,
		&philo->table->threads_running_num);
	// tenemos que setear la ultima comida que hacen
	while (!simulation_finished(philo->table))
	{
		//1) Estoy lleno??
		if (philo->full)
			break ;
		philo_eat(philo);
		print_status(SLEEP, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		//4)Think
		philo_think(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_limit_meals == 0)
		return ; //vuelta al main y limpiamos
	else if (table->philo_nbr == 1)
		;
		// tenemos que crear esto
	else
	{
		while (++i < table->philo_nbr)
			thread_handle(&table->philos[i].thread_id,
				dinner_sim, &table->philos[i], CREATE);
	}
	// Antes de esto tenemos que monitorear nuestro codigo para 
	//comprobar si un filosofo ha muerto o no.
	thread_handle(&table->monitor_thread, monitor, table, CREATE);
	// start of simulation
	table->start_sim = get_time(MILISECOND);
	//despues de todo esto los threads estaran listo por lo que seteamos a 1 threads ready
	set_int(&table->mutex_table, &table->threads_ready, 1);
	//Una vez que hemos hecho todo esto esperamos a que todos hayan terminado y hacemos un join.
	i = -1;
	while (++i < table->philo_nbr)
		thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	//si conseguimos llegar a esta linea podemos decir que todos los filosofos han comido
	// o lo que es lo mismo podemos decir que estan llenos (full)
}
/*Despues de la funcion de arriba podemos decir
que todos los hilos han sido creados asi que podemos 
setear el booleano de threads_ready en true. */
