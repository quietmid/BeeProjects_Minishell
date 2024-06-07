/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:27:38 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/05 17:36:03 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arr(char **arr)
{
	int	x;

	x = 0;
	if (!arr || !arr[x])
		return ;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
	return ;
}

/*
* calculate len of array
*/
int	ft_arr_len(char **array)
{
	int	x;

	x = 0;
	while (array[x])
	{
		x++;
	}
	return (x);
}

/*
* malloc a copy of an array
*/
char	**ft_arr_copy(char **arr)
{
	char	**res;
	int		x;

	x = 0;
	res = malloc(sizeof(char *) * (ft_arr_len(arr) + 1));
	// if (!new_array)
	// 	"malloc error"
	while (arr[x])
	{
		res[x] = ft_strdup(arr[x]);
		if (!res[x])
		{
			ft_free_arr(res);
			// "malloc error"
		}
		x++;
	}
	res[x] = NULL;
	return (res);
}

/*
* print an array of strings + \n
*/

void	ft_arr_print(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		ft_putstr_fd(arr[x], 1);
		ft_putchar_fd('\n', 1);
		x++;
	}
}
