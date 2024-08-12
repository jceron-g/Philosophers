/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:40:52 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/12 10:50:20 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//./philo 5(philo) 800(time2die) 200(time2eat) 200(time2sleep) [5] (nº meals)
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 | argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean_table(&table);
	}
	else
		print_error("Wrong input.\n");
}
