/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/05 17:53:58 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(t_data *data)
{
	char	*tmppwd;
	char	*home;

	tmppwd = data->pwd;
	home = getenv("HOME");
	// if (!home)
	// 	"home not set"
	if (chdir(home) == 0)
	{
        printf("in directory");
		data->oldpwd = tmppwd;
		data->pwd = home;
	}
	//else
		// error
}
/*
* execute builtin command run
*/
void	run_cd(t_data *data)
{
	//int	x;
	int	flag;
	//int	start;

	flag = 0;
	if (!data->line[1])
	{
		go_home(data);
	}
// 	else
// 	{
		
// 	}

// 		x = 1;
// 		start = 1;
// 		while (data->line[x] && is_nflag(data->line[x]) == TRUE)
// 		{
// 			flag = 1;
// 			x++;
// 			start = x;
// 		}
// 		while (data->line[start])
// 		{
// 			ft_putstr_fd(data->line[start], 2);
// 			if (start < (ft_arr_len(data->line) - 1))
// 				ft_putstr_fd(" ", 2);
// 			start++;
// 		}
// 	}
// 	else if (flag == 0 || (flag == 1 && ft_arr_len(data->line) == 2))
// 		ft_putstr_fd("\n", 2);
}