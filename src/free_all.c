/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:01:21 by jlu               #+#    #+#             */
/*   Updated: 2024/07/17 14:39:34 by jlu              ###   ########.fr       */
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

void	ft_free_before_loop(t_data *data)
{
	int i;

	i = 0;
	// while (i < data->cmd_count)
	// {
	// 	if (data->token[i].cmd)
	// 		ft_free_arr(data->token[i].cmd);
	// 	if (data->token[i].redir)
	// 		ft_free_tri(data->token[i].redir);
	// 	free(&data->token[i]);
	// 	i++;
	// }
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
	int i;

	i = 0;
	while (i < data->cmd_count)
	{
		
		printf("token addr: %p\n", &data->token[i]);
		if (data->token[i].cmd)
			ft_free_arr(data->token[i].cmd);
		printf("debug\n");
		if (data->token[i].redir)
			ft_free_tri(data->token[i].redir);
		if (data->token[i].hd)
		{
			printf("freehdfile\n");
			free(data->token[i].hdfile);
		}
		i++;
	}
	free(data->token);
	printf("token freed\n");
}

void	free_single_token(t_data *data, int i)
{
	if (data->token[i].cmd)
		ft_free_arr(data->token[i].cmd);
	if (data->token[i].redir)
		ft_free_tri(data->token[i].redir);
	free(&data->token[i]);
}

void	ft_envclear(t_env **env)
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

// void	ft_free_env(t_env *env)
// {
// 	t_env *tmp;

// 	printf("free env\n");
// 	while (env)
// 	{
// 		free(env->key);
// 		free(env->value);
// 		tmp = env;
// 		env = env->next;
// 		free(tmp);
// 		tmp = NULL;
// 	}
// }

void free_data_all(t_data *data, int type)
{
	(void)type;
	// int i;

	// i = -1;

	// if (type == 1)
	// 	printf("here\n");
	if (data->token)
	 	ft_free_token(data);
    // // if (data->pid)
    // //     free(data->pid);
    // if (data->pipe)
	// {
    //     while (++i < data->pipe_count)
	// 		free(data->pipe[i]);
	// }
	// if (data->paths)
	// 	ft_free_arr(data->paths);
	// if (data->path_cmd)
	// 	free(data->path_cmd);
	// if (data->env_arr)
	// 	ft_free_arr(data->env_arr);
	// dprintf(1, "bENV : %d\n", ft_envsize(data->env));
	// if (ft_envsize(data->env) != 0)
	//  	ft_envclear(&data->env);
	// dprintf(1, "aENV : %d\n", ft_envsize(data->env));
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
	 	free(data->oldpwd);
}

// void free_all(t_data *data)
// {
// 	if (data->token)
// 		ft_free_token(data);
// }