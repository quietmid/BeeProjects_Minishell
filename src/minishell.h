/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:51:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/01 18:27:06 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//libft library
# include "../libft/libft.h"

//library headers
# include <unistd.h> // write dup fork
# include <stdio.h> // printf readline 
# include <stdlib.h> // malloc free
# include <sys/wait.h> // waitpid
# include <string.h>
# include <sys/types.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

//struct

typedef struct s_data
{
	char	**envp;
	char	**paths;
	char	**line;
}		t_data;

//functions

//builtin
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data);

//shell utils
char	*find_path(char **envp);
char	**get_paths(char **envp);
void	signal_setup(void);
void	sigint_handler(int sig);

//basic utils
int		ft_arrlen(char **array);

#endif