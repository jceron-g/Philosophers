/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:02:31 by jceron-g          #+#    #+#             */
/*   Updated: 2024/07/03 20:22:39 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../lib/libft/libft.h"

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	
	
	
}				t_philo


#endif