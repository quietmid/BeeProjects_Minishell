/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:02:11 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/19 18:11:28 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

static void	print_errors(char *errmsg, char *str, char c)
{
	ft_putstr_fd(errmsg, 2);
	if (c)
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd(" newline", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(" \"\n", 2);
}

void	error(t_data *data, t_error code, int e)
{
	if (code == XMALLOC)
		ft_putstr_fd(ERR_MALLOC, 2);
	if (code == XPIPE)
		ft_putstr_fd(ERR_PIPE, 2);
	if (code == XFORK)
		ft_putstr_fd(ERR_FORK, 2);
	if (code == XEXEC)
		ft_putstr_fd(ERR_EXEC, 2);
	if (code == XHD)
		ft_putstr_fd(ERR_HD, 2);
	if (code == XCWD)
		ft_putstr_fd(ERR_CWD, 2);
	ft_free_token(data);
	ft_free_before_loop(data);
	exit (e);
}

void	error_cd(t_data *data, t_error code, char *var, char c)
{
	(void)data;
	ft_putstr_fd("minishell-8.8$: ", 2);
	if (code == XCD)
	{
		ft_putstr_fd("cd: ", 2);
		perror(var);
	}
	else if (code == XEXP)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": "ERR_EXP, 2);
	}
	else if (code == XCDHOME)
		ft_putendl_fd(ERR_HOME, 2);
	else if (code == XCDOLDPWD)
		ft_putendl_fd(ERR_OLDPWD, 2);
	else if (code == XSYNTAX)
		print_errors(ERR_SYNTAX, NULL, c);
}

void	error_var(t_data *data, t_error code, char *var, int e)
{
	if (code == XCMD)
	{
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": "ERR_CMD, 2);
	}
	else
	{
		ft_putstr_fd("minishell-8.8$: ", 2);
		if (code == XNOFILE || code == XDIR)
		{
			ft_putstr_fd(var, 2);
			if (code == XNOFILE)
				ft_putendl_fd(": "ERR_NOFILE, 2);
			else if (code == XDIR)
				ft_putendl_fd(": "ERR_DIR, 2);
		}
		else
			perror(var);
	}
	ft_free_token(data);
	ft_free_before_loop(data);
	data->status = (WEXITSTATUS(e));
	exit (e);
}
