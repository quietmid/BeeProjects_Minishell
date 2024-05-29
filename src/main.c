/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:28 by jlu               #+#    #+#             */
/*   Updated: 2024/05/29 17:29:40 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_minishell()
{
	int file;
	char *line;
	char *end;

	file = open(".temp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file < 0) // 
		exit(EXIT_FAILURE);
	write (1, "minishell-8.8$", 14);
	line = readline("> ");
	//end = ft_strjoin("exit", "\n");
	end = "exit";
	while (ft_strcmp(line, end) != 0)
	{
		write (1, "minishell-8.8$", 14);
		ft_putstr_fd(line, file);
		free(line);
		line = readline("> ");
	}
	free(line);
	//free(end);
}

int main(int ac, char **ag, char **envp)
{
	if (ac != 1) // probably don't need
		return (0);
	ft_minishell();
	// start the program
	// free all the shit
	return (0);
}