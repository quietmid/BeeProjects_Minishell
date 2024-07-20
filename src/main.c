/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/07/20 19:20:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_children(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->cmd_count)
	{
		waitpid(data->pid[x], &data->status, 0);
		x++;
	}
	return ;
}

void	execute(t_data	*data)
{
	if (data->cmd_count == 1 && is_builtin(data) == TRUE)
	{
		if (data->token[0].redir != NULL)
			redirect_builtin(data, 0);
		exec_builtin(data, 0);
		if (data->token[0].redir != NULL)
			restore_stdio(data, 0);
		free_single_token(data, 0);
	}
	else
	{
		create_pipes(data);
		create_forks(data);
		close_pipes(data);
		wait_children(data);
		ft_free_token(data);
		ft_free_before_loop(data);
	}
	return ;
}
/* we can use this one if we want improve user experience*/

// static void	line_history(char *line)
// {
// 	static char	*last = NULL;

// 	if (*line && (!last || ft_strcmp(last, line)))
// 	{
// 		add_history(line);
// 		free(last);
// 		last = ft_strdup(line);
// 	}
// }

void	signal_d(void)
{
	if (isatty(0))
		ft_putendl_fd("exit", 2);
	exit (0);
}

void	ft_minishell(t_data *data, int status)
{
	char	*line;

	toggle_input(SIG_PARENT);
	while (1)
	{
		signal_setup(SIG_PARENT);
		status = 1;
		line = readline("\033[0;31mminishell-8.8$ \033[0m");
		if (!line)
			signal_d();
		if (line && *line != '\0')
		{
			add_history(line);
			status = prompt_check(data, line);
			if (status == 1)
				status = parse_start(data, line);
			if (status == 1)
				execute(data);
			if (status == 0)
				ft_free_token(data);
		}
		if (line)
			free(line);
	}
	toggle_input(SIG_CHILD);
}

int	main(int ac, char **ag, char **envp)
{
	t_data	data;
	int		status;

	(void)ac;
	(void)ag;
	data = (t_data){0};
	status = 1;
	if (ac != 1)
		return (0);
	env_setup(&data, envp);
	ft_minishell(&data, status);
	return (0);
}
