/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:40:39 by jceron-g          #+#    #+#             */
/*   Updated: 2024/08/13 12:37:54 by jceron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char c)
{
	if (c < '0' || c > '9')
	{
		printf("Error: Argument must be a number\n");
		return (1);
	}
	return (0);
}

static int	check_num(long num)
{
	if (num > 2147483647)
	{
		printf("Argument can't be maximum int\n");
		return (1);
	}
	if (num < 0)
	{
		printf("Argument must be positive\n");
		return (1);
	}
	return (0);
}

long	ft_atol(char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (is_number(*str))
		return ((long)-2);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (check_num(num * sign))
		return ((long)-2);
	return (num);
}
