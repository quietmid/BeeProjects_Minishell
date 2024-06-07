/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:51:28 by jlu               #+#    #+#             */
/*   Updated: 2024/06/07 13:16:05 by jlu              ###   ########.fr       */
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
typedef enum e_metachar
{
	PIPE = 124,
	DOLLAR = 36,
	INDIRECT = 60,
	OUTDIRECT = 62,
	SINGLEQ = 39,
	DOUBLEQ = 34,
	QUESTIONM = 63,
}	t_metachar;

typedef enum e_mode
{
		SIG_PARENT = 0,
		SIG_HEREDOC = 1,
		SIG_CHILD = 2,
}		t_mode;

typedef enum e_token_type
{
	NO_TOKEN, // 0
	PIPE_TOKEN, // | 1
	HERE_DOC_TOKEN, // << 2 
	REDIR_IN_TOKEN,	 // < 3
	REDIR_OUT_TOKEN, // > 4 
	REDIR_APP_OUT_TOKEN, // >> 5
	STRING_TOKEN, // 6
	DOLLAR_TOKEN, // $ 7
	INFILE_TOKEN, // 8
	OUTFILE_TOKEN, // 9
	OUTFILE_TRUNC_TOKEN, // 10
	DELIM_TOKEN, // 11
}	t_token_type;

typedef struct s_parse
{
	int	cmd_n;
}	t_parse;

typedef struct s_token
{
	int				idx;
	char 			*input;
	t_token_type	type;
	//struct s_token	*next;
	//struct s_token 	*prev;
} 	t_token;

typedef struct s_data
{
	char	***argv;
	char	**envp;
	char	**paths;
	char	**line;
	int		cmd_count;
	t_token token[100];
	struct s_parse *par;
}		t_data;

//functions

//builtin
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data);

// signals
void	heredoc_handler(int sig);
void	signal_setup(int mode);
void	sig_handler(int sig);

// Parsing
void	parse(t_data *data, const char *line);
void	space_replace(char *str);
void	assign_token(char *input, t_token *token, int idx);
int		parse_start(t_data *data, char *line);
//int		parse_start(char *line);
int		pipe_scans(char *line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token_type deter_token_type(char *input);

//shell utils
char	*find_path(char **envp);
char	**get_paths(char **envp);
void	rl_replace_line(const char *text, int clear_undo);

//basic utils
int		ft_arrlen(char **array);
void	ft_free_arr(char **array);

#endif