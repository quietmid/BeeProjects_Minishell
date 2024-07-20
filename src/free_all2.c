/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:52:31 by jlu               #+#    #+#             */
/*   Updated: 2024/07/20 17:13:40 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tri(char ***tri)
{
	int	i;

	i = 0;
	if (tri)
	{
		while (tri[i])
		{
			ft_free_arr(tri[i]);
			i++;
		}
		free(tri);
		tri = NULL;
	}
}

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
}
