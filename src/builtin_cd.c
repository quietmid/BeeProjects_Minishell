/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:21:19 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/07 21:45:02 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* update env key to pwd;
*/
void	update_env(t_data *data, char *key)
{
	t_env	*node;
	char	*tmp;

	node = search_env(data, key);
	if (node)
	{
		tmp = getcwd(NULL, 0);
		// if (!tmp)
		// 	"malloc error"
		node->value = tmp;
	}
}
/*
* execute cd HOME
*/
void	go_to_home(t_data *data)
{
	t_env	*node;

	node = search_env(data, "HOME");
	if (node)
	{
		if (chdir(node->value) == 0)
			update_env(data, "PWD");
		// else
		// 	"chdir error"
	}
	// else
	// 	"error home not set"
}
/*
* execute cd "dir"
*/
char	*check_address(t_data *data)
{
	char	*res;
	//char	*tmp;

	if (data->line[1][0] == '/')
		res = data->line[1];
	else
		res = ft_strjoin("./", data->line[1]);
	return (res);
}
/*
* execute builtin command cd
*/
void	run_cd(t_data *data)
{
	char	*add;

	// if (ft_arr_len(data->line)  > 2)
	// {
	// 	"error to many arguments"
	// }
	if (!data->line[1])
	{
		update_env(data, "OLDPWD");
		go_to_home(data);
	}
	else
	{
		add = check_address(data);
		if (chdir(add) == 0)
			update_env(data, "PWD");
		else
		 	printf("chdir error"); // chdir errors
	}
}
