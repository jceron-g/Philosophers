/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:40:52 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/08 11:10:02 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//./philo 5(philo) 800(time2die) 200(time2eat) 200(time2sleep) [5] (nº meals)
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 | argc == 6)
	{
		//correct input
		//esta funcion mira errors checking, filling table table
		parse_input(&table, argv);
		//2)
		data_init(&table);
		dinner_start(&table);
		//3)
		//dinner_start(&table);
		//4) No leaks philos are full or 1 philo dies
		//clean(&table);
	}
	else
		print_error("Wrong input.\n");
}
