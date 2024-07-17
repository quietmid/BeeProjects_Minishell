/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/07/17 14:24:03 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* TEST EXECUTE*/ //delete later
void	execute(t_data	*data)
{
	if (data->cmd_count == 1 && is_builtin(data) == TRUE)
	{
		if (data->token[0].redir != NULL)
			redirect_builtin(data, 0);	
		exec_builtin(data);
		if (data->token[0].redir != NULL)
			restore_stdio(data, 0);
		free_single_token(data, 0);
	}
	else
	{
		create_pipes(data);
		create_forks(data);
		close_pipes(data);
		int x;
		x = 0;
		while (x < data->cmd_count)
		{
			waitpid(data->pid[x], &data->status, 0);
			x++;
		}
		// dprintf(1, "status: %d\n", WEXITSTATUS(data->status));
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

void	signal_d()
{
	if (isatty(0))
		write (2, "exit", 5);
	exit (0);
}

void	ft_minishell(t_data *data)
{
	char	*line;
	int		status;

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
			if (status)
				status = parse_start(data, line);
			if (status)
			 	execute(data);
		}
		if (line)
			free(line);
    }
	// free(line);
	toggle_input(SIG_CHILD);
}

int main(int ac, char **ag, char **envp)
{
	t_data	data;

	(void)ac;
	(void)ag;
	data = (t_data){0};
	if (ac != 1) // probably don't need
		return (0);
	env_setup(&data, envp);
	ft_minishell(&data);
	//free_data_all(&data, 0);
	// start the program
	// free all the shit
	//free_data_all(&data, 1);
	return (0);
}
