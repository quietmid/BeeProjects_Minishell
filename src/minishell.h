/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:51:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/05 17:33:42 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//libft library
# include "../libft/libft.h"

//library headers
# include <unistd.h> // write dup fork chdir
# include <stdio.h> // printf readline 
# include <stdlib.h> // malloc free getenv
# include <sys/wait.h> // waitpid
# include <string.h>
# include <sys/types.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0
//struct

typedef struct s_data
{
	char	**envp;
	char	**paths;
	char	*pwd;
	char	*oldpwd;
	char	**line;
}		t_data;

//functions

//builtin
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data);
void	run_echo(t_data *data);
void	run_pwd(t_data *data);
void	run_cd(t_data *data);

//envp
void	env_setup(t_data *data, char **envp);

//shell utils
void	signal_setup(void);
void	sig_handler(int sig);
void	rl_replace_line(const char *text, int clear_undo);

//basic utils
char	**ft_arr_copy(char **arr);
int		ft_arr_len(char **array);
void	ft_free_arr(char **arr);
void	ft_arr_print(char **arr);

#endif