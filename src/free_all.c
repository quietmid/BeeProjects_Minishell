/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:01:21 by jlu               #+#    #+#             */
/*   Updated: 2024/07/09 19:39:02 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tri(char ***tri)
{
	int i;

	i = 0;
	if (tri)
	{
		while (tri[i])
		{
			ft_free_arr(tri[i]);
			// free(tri[i]);
			i++;
		}
		free(tri);
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
	arr = NULL;
}
void	ft_free_token(t_data *data)
{
	int i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (data->token[i].cmd)
			ft_free_arr(data->token[i].cmd);
		if (data->token[i].redir)
			ft_free_tri(data->token[i].redir);
		free(&data->token[i]);
		i++;
	}
}

void	ft_free_env(t_env *env)
{
	t_env *tmp;

	printf("free env\n");
	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
		tmp = NULL;
	}
}

void free_data_all(t_data *data, int type)
{
	int i;

	i = -1;

	if (type == 1)
		printf("here\n");
	if (data->token)
		ft_free_token(data);
    if (data->pid)
        free(data->pid);
    if (data->pipe)
	{
        while (++i < data->pipe_count)
			free(data->pipe[i]);
	}
	// if (data->argv)
	// 	ft_free_tri(data->argv);
	if (data->paths)
		ft_free_arr(data->paths);
	if (data->path_cmd)
		free(data->path_cmd);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	if (data->env_arr)
		ft_free_arr(data->env_arr);
	if (data->env)
		ft_free_env(data->env);
}

// void free_all(t_data *data)
// {
	
// }