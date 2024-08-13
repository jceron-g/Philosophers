/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:40:52 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/13 12:32:28 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 | argc == 6)
	{
		if (parse_input(&table, argv) != 0)
			return (1);
		data_init(&table);
		dinner_start(&table);
		clean_table(&table);
		return (0);
	}
	else
		printf("Wrong input.\n");
	return (1);
}
