/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:56:48 by jceron-g          #+#    #+#             */
/*   Updated: 2024/07/12 23:30:53 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*protected_malloc(size_t bytes)
{
	void	*aux;
	
	aux = malloc(bytes);
	if (aux == NULL)
		print_error("Error during malloc");
	return (aux);
}
/* Estas funciones se encargan de proteger los mutex mediante el codigo
de error que aparecen en el man para los distintos tipos de pthread que hay
ya sea lock, init etc etc con la llamada a status una vez el pthread devuelva el
numero correcto se hará el comando que se haya pedido segun el Mutex code (mcode)*/

static	void check_mutex_error(int status, t_mcode mcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (LOCK == mcode || UNLOCK == mcode || DESTROY == mcode))
		print_error("The value specified by mutex is invalid.");
	else if (status == EINVAL && INIT == mcode)
		print_error("The value specified by atrr is invalid.");
	else if (status == EDEADLK)
		print_error("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		print_error("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		print_error("The process cannot allocat enough memory to create another mutex.");
	else if (status == EBUSY)
		print_error("Mutex is locked.");
}

void	mutex_handle(pthread_t *mutex, t_mcode mcode)
{
	if (LOCK == mcode)
		check_mutex_error(pthread_mutex_lock(mutex), mcode);
	else if (UNLOCK == mcode)
		check_mutex_error(pthread_mutex_unlock(mutex), mcode);
	else if (INIT == mcode)
		check_mutex_error(pthread_mutex_init(mutex, NULL), mcode);
	else if (DESTROY == mcode)
		check_mutex_error(pthread_mutex_destroy(mutex), mcode);
	else
		print_error("Wrong code for mutex handle");
}
/*Para hilos se hara lo mismo*/

static	void check_thread_error(int status, t_mcode mcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("No resource to create another thread.");
	else if (status == EPERM)
		print_error("The caller does ot have appropriate permission.");
	else if (status == EINVAL && CREATE == mcode)
		print_error("The value specified by attr is invalid.");
	else if (status == EINVAL && (JOIN == mcode || DETACH == mcode))
		print_error("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		print_error("No thread could be found corresponding to that"
		"specified by the given thread ID, thread.");
	else if (status == EDEADLK)
		print_error("A deadlock was detected or the value of"
		"thread specifies the calling thread.");
}
void	thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_mcode mcode)
{
	if (CREATE == mcode)
		check_thread_error(pthread_create(thread, NULL, foo, data), mcode);
	else if (JOIN == mcode)
		check_thread_error(pthread_join(*thread, NULL), mcode);
	else if (DETACH == mcode)
		check_thread_error(pthread_detach(*thread), mcode);
	else
		print_error("Wrong code for thread handle");
}
