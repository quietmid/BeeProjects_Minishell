/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:30:18 by jlu               #+#    #+#             */
/*   Updated: 2024/07/16 14:30:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
* print an array of strings + \n DEBUGG
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

/*
* calculate the size of the env ll
*/
int	ft_envsize(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
