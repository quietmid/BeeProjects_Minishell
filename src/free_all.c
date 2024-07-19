/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:01:21 by jlu               #+#    #+#             */
/*   Updated: 2024/07/19 17:53:00 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_before_loop(t_data *data)
{
	int	i;

	i = 0;
	if (data->pid)
		free(data->pid);
	if (data->pipe)
	{
		while (i < data->pipe_count)
		{
			free(data->pipe[i]);
			i++;
		}
		free(data->pipe);
	}
}

void	ft_free_token(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (data->token[i].cmd)
			ft_free_arr(data->token[i].cmd);
		if (data->token[i].redir)
			ft_free_tri(data->token[i].redir);
		if (data->token[i].hd)
			free(data->token[i].hdfile);
		if (data->token[i].cmd_line)
			free(data->token[i].cmd_line);
		i++;
	}
	free(data->token);
}

void	free_single_token(t_data *data, int i)
{
	if (data->token[i].cmd)
		ft_free_arr(data->token[i].cmd);
	if (data->token[i].redir)
		ft_free_tri(data->token[i].redir);
	if (data->token[i].cmd_line)
		free(data->token[i].cmd_line);
	free(&data->token[i]);
}

static void	ft_envclear(t_env **env)
{
	t_env	*current;

	if (!env)
		return ;
	while (*env)
	{
		current = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = current;
	}
	*env = NULL;
}

void	free_data_all(t_data *data, int type)
{
	(void)type;
	if (data->token)
		ft_free_token(data);
	if (ft_envsize(data->env) != 0)
		ft_envclear(&data->env);
}
