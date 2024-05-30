/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/05/30 15:42:59 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_minishell(t_data *data)
{
	int file;
	char *line;
	char *end;

	file = open(".temp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file < 0) // 
		exit(EXIT_FAILURE);
	line = readline("minishell-8.8$ ");
	end = "exit";
	while (ft_strcmp(line, end) != 0)
	{
		ft_putstr_fd(line, file);
		// if (parse the line == cmd)
		// 		execute the cmd
		// else
		// 		minishell-8.8$: "line": command not found
		free(line);
		line = readline("minishell-8.8$ ");
	}
	free(line);
	unlink(".temp"); // unlink temp when all finished
}

int main(int ac, char **ag, char **envp)
{
	t_data	data;
	
	data = (t_data){0};
	ag = NULL;
	data.path = find_path(envp);
	if (ac != 1) // probably don't need
		return (0);
	ft_minishell(&data);
	// start the program
	// free all the shit
	return (0);
}