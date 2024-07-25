/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:02:11 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/25 19:30:00 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_msg(t_data *data, t_error code, char *err, char *var)
{
	char	*tmp;
	char	*msg;

	if (code == XCMD)
	{
		tmp = ft_strjoin(var, err);
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
		ft_putendl_fd(tmp, 2);
	}
	else
	{
		tmp = ft_strjoin(var, err);
		if (!tmp)
			error(data, XMALLOC, EXIT_FAILURE);
		msg = ft_strjoin("minishell-8.8$: ", tmp);
		if (!msg)
			error(data, XMALLOC, EXIT_FAILURE);
		free (tmp);
		ft_putendl_fd(msg, 2);
		free (msg);
	}
}

void	error_fd(t_data *data, int err, char *var, int e)
{
	if (err == EACCES)
	{
		print_err_msg(data, XPERM, ERR_PERM, var);
	}
	else if (err == ENOENT)
	{
		print_err_msg(data, XNOFILE, ERR_NOFILE, var);
	}
	data->ms_stat = 1;
	data->status = e;
}

void	error_var(t_data *data, t_error code, char *var, int e)
{
	if (code == XCMD)
	{
		print_err_msg(data, XCMD, ERR_CMD, var);
	}
	else
	{
		if (code == XNOFILE || code == XDIR)
		{
			if (code == XNOFILE)
				print_err_msg(data, XNOFILE, ERR_NOFILE, var);
			else if (code == XDIR)
				print_err_msg(data, XDIR, ERR_DIR, var);
		}
		else
			perror(var);
	}
	data->ms_stat = 1;
	data->status = e;
}
