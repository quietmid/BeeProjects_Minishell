/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/06 17:29:38 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* execute builtin command run
*/
void	run_cd(t_data *data)
{
	char	*add;
	
	//pwd = data->pwd;
	if (!data->line[1])
	{
		add = getenv("HOME");
		// if (!add)
		// 	error
		chdir(add);
	}
	else
	{
		add = data->line[1];
		chdir(add);
		
	}
}
