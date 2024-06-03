/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:51:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/03 16:57:17 by jlu              ###   ########.fr       */
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
# include <termios.h>

# include <readline/readline.h>
# include <readline/history.h>

//struct

typedef enum e_mode
{
		SIG_PARENT = 0,
		SIG_HEREDOC = 1,
		SIG_CHILD = 2,
}		t_mode;

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

// signals
void	heredoc_handler(int sig);
void	signal_setup(int mode);
void	sig_handler(int sig);

//shell utils
char	*find_path(char **envp);
char	**get_paths(char **envp);
void	rl_replace_line(const char *text, int clear_undo);

//basic utils
int		ft_arrlen(char **array);

#endif