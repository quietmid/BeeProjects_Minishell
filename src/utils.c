/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:27:38 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/04 15:27:35 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* calculate len of array
*/
int	ft_arrlen(char **array)
{
	int	x;

	x = 0;
	while (array[x])
	{
		x++;
	}
	return (x);
}
