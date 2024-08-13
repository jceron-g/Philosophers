/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:56:48 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/13 12:32:54 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*protected_malloc(size_t bytes)
{
	void	*aux;

	aux = malloc(bytes);
	if (aux == NULL)
		printf("Error during malloc");
	return (aux);
}

static void	check_mutex_error(int status, t_mcode mcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (LOCK == mcode
			|| UNLOCK == mcode || DESTROY == mcode))
		printf("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && INIT == mcode)
		printf("The value specified by atrr is invalid.\n");
	else if (status == EDEADLK)
		printf("A deadlock would occur if "
			"the thread blocked waiting for mutex.\n");
	else if (status == EPERM)
		printf("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		printf("The process cannot allocate "
			"enough memory to create another mutex.\n");
	else if (status == EBUSY)
		printf("Mutex is locked.\n");
}

void	mutex_handle(pthread_mutex_t *mutex, t_mcode mcode)
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
		printf("Wrong code for mutex handle.\n");
}

static void	check_thread_error(int status, t_mcode mcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		printf("No resource to create another thread.\n");
	else if (status == EPERM)
		printf("The caller does ot have appropriate permission.\n");
	else if (status == EINVAL && CREATE == mcode)
		printf("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (JOIN == mcode || DETACH == mcode))
		printf("The value specified by thread is not joinable\n.");
	else if (status == ESRCH)
		printf("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		printf("A deadlock was detected or the value of"
			"thread specifies the calling thread.\n");
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
		printf("Wrong code for thread handle.\n");
}
