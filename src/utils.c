/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:30:18 by jlu               #+#    #+#             */
/*   Updated: 2024/07/18 22:30:09 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	**ft_arr_copy(char **arr)
// {
// 	char	**res;
// 	int		x;

// 	x = 0;
// 	res = malloc(sizeof(char *) * (ft_arr_len(arr) + 1));
// 	if (!res)
// 		error(data, XMALLOC, EXIT_FAILURE);
// 	while (arr[x])
// 	{
// 		res[x] = ft_strdup(arr[x]);
// 		if (!res[x])
// 		{
// 			ft_free_arr(res);
// 			error(data, XMALLOC, EXIT_FAILURE);
// 		}
// 		x++;
// 	}
// 	res[x] = NULL;
// 	return (res);
// }

/*
* print an array of strings + \n DEBUGG
*/

// void	ft_arr_print(char **arr)
// {
// 	int	x;

// 	x = 0;
// 	while (arr[x])
// 	{
// 		ft_putstr_fd(arr[x], 1);
// 		ft_putchar_fd('\n', 1);
// 		x++;
// 	}
// }
