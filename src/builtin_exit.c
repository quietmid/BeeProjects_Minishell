/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:22:11 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/24 22:19:37 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	convert_code(t_data *data, char *str)
{
	int	num;

	num = (ft_atoi(str) % 256);
	data->status = num;
}

static int	is_digit(t_data *data, char *str)
{
	int	x;

	(void)data;
	x = 0;
	if (str[0] == '-' || str[0] == '+')
		x++;
	while (str[x])
	{
		if (ft_isdigit(str[x]) == 0)
			return (FALSE);
		x++;
	}
	return (TRUE);
}

static void	exit_message(t_data *data, char *var, int c)
{
	char	*tmp;
	char	*msg;

	(void)data;
	if (c == 1)
		ft_putendl_fd("minishell-8.8$: exit: too many arguments", 2);
	else if (c == 2)
	{
		tmp = ft_strjoin(var, ": numeric argument required");
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
		msg = ft_strjoin("minishell-8.8$: exit: ", tmp);
		if (!msg)
			error(data, XMALLOC, EXIT_FAILURE);
		free (tmp);
		ft_putendl_fd(msg, 2);
		free(msg);
	}
}

void	run_exit(t_data *data, int x)
{
	if (ft_arr_len(data->token[x].cmd) > 1)
	{
		if (is_digit(data, data->token[x].cmd[1]) == FALSE)
		{
			exit_message(data, data->token[x].cmd[1], 2);
			data->status = 2;
		}
		else if (is_digit(data, data->token[x].cmd[1]) == TRUE
			&& ft_arr_len(data->token[x].cmd) == 2)
			convert_code(data, data->token[x].cmd[1]);
		else
		{
			if (data->cmd_count == 1)
				ft_putstr_fd("exit\n", 1);
			exit_message(data, NULL, 1);
			data->status = 1;
			return ;
		}
	}
	if (data->cmd_count == 1)
		ft_putstr_fd("exit\n", 1);
	free_data_all(data, 0);
	exit(data->status);
}
