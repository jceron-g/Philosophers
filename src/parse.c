/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:24:12 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/13 12:53:09 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
	{
		printf("Time has to be greater than 60 ms\n");
		return (1);
	}
	if (argv[5])
	{
		table->num_limit_meals = ft_atol(argv[5]);
		if (table->num_limit_meals <= 0)
			return (1);
	}
	else
		table->num_limit_meals = -1;
	return (0);
}
