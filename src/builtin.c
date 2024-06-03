/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:50:33 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/01 19:14:28 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* execute builtin command echo (-n)
*/
void	run_echo(t_data *data)
{
	int	x;
	int	n;
	int	start;

	n = 0;
	x = 1;
	start = 1;
	if (ft_strncmp(data->line[x], "-n", 2) == 0)
	{
		n = 1;
		start++;
		x++;
	}
	while (data->line[x])
	{
		if (x > start && x < ft_arrlen(data->line))
			ft_putstr_fd(" ", 2);
		ft_putstr_fd(data->line[x], 2);
		x++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 2);
}

/*
* check first string in input if builtin, return 1 if true 0 if false
*/
int	is_builtin(t_data *data)
{
	if (data->line[0] == NULL)
		return (0);
	else if (ft_strcmp(data->line[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(data->line[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(data->line[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->line[0], "export") == 0)
		return (1);
	else if (ft_strcmp(data->line[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(data->line[0], "env") == 0)
		return (1);
	else if (ft_strcmp(data->line[0], "exit") == 0)
		return (1);
	else
		return (0);
}
/*
* execute builtin commands
*/
void	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->line[0], "echo") == 0)
        run_echo(data);
	// else if (ft_strcmp(data->line[0], "cd") == 0)
	// else if (ft_strcmp(data->line[0], "pwd") == 0)
	// else if (ft_strcmp(data->line[0], "export") == 0)
	// else if (ft_strcmp(data->line[0], "unset") == 0)
	// else if (ft_strcmp(data->line[0], "env") == 0)
	else if (ft_strcmp(data->line[0], "exit") == 0)
		exit(0);
}

