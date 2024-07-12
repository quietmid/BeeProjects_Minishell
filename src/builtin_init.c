/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:50:33 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/12 19:10:29 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *data)
{
	if (data->token[0].cmd[0] == NULL)
		return (FALSE);
	if (ft_strcmp(data->token[0].cmd[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(data->token[0].cmd[0], "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(data->token[0].cmd[0], "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(data->token[0].cmd[0], "export") == 0)
		return (TRUE);
	else if (ft_strcmp(data->token[0].cmd[0], "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(data->token[0].cmd[0], "env") == 0)
		return (TRUE);
	else if (ft_strcmp(data->token[0].cmd[0], "exit") == 0)
		return (TRUE);
	else
		return (0);
}

void	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->token[0].cmd[0], "echo") == 0)
		run_echo(data);
	if (ft_strcmp(data->token[0].cmd[0], "cd") == 0)
		run_cd(data);
	else if (ft_strcmp(data->token[0].cmd[0], "pwd") == 0)
		run_pwd(data);
	else if (ft_strcmp(data->token[0].cmd[0], "export") == 0)
		run_export(data);
	else if (ft_strcmp(data->token[0].cmd[0], "unset") == 0)
		run_unset(data);
	else if (ft_strcmp(data->token[0].cmd[0], "env") == 0)
		run_env(data);
	else if (ft_strcmp(data->token[0].cmd[0], "exit") == 0)
	{
		free_data_all(data, 0);
		exit(0);
	}
}
