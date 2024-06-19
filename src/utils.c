/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:27:38 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/19 18:51:14 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*free array of strings*/

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

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;
// 	int	result;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
// 	{
// 		i++;
// 	}
// 	result = (s1[i] - s2[i]);
// 	return (result);
// }