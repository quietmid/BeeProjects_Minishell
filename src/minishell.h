/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:51:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/06 22:37:46 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//libft library
# include "../libft/libft.h"

//library headers
# include <unistd.h> // write dup fork getcwd chdir
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

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char	**line; // to be removed
	char	*path_cmd;
	char	**envi;
	int		status;
	t_env	*env;
}			t_data;


//functions

//builtin
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data);
void	run_echo(t_data *data);
void	run_cd(t_data *data);

//envp
void	env_setup(t_data *data, char **envp);
t_env	*search_env(t_data *data, char *str);
void	env_to_arr(t_data *data);
int		ft_envsize(t_env *lst);

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