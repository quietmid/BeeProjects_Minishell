/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:00:05 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/19 18:25:53 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//libft library & h.files
# include "../libft/libft.h"
# include "./errors.h"

//library headers
# include <unistd.h> // write dup fork
# include <stdio.h> // printf readline
# include <stdlib.h> // malloc free
# include <sys/wait.h> // waitpid
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h> //stat
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0

extern int	g_sigint;

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
}	t_mode;

typedef struct s_token
{
	int				idx;
	int				redir_len;
	int				cmd_len;
	int				in;
	int				out;
	int				hd;
	char			*cmd_line;
	char			*hdfile;
	char			**cmd;
	char			***redir;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	int				parent_in;
	int				parent_out;
	int				*pid;
	int				**pipe;
	int				status;
	int				arr_len;
	int				hd;
	char			**paths;
	char			**env_arr;
	char			*path_cmd;
	int				cmd_count;
	int				pipe_count;
	char			*pwd;
	char			*oldpwd;
	t_env			*env;
	t_token			*token;
	struct s_parse	*par;
}					t_data;

//builtin
int		is_builtin_x(t_data *data, int x);
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data);
void	run_echo(t_data *data);
void	run_cd(t_data *data);
void	run_pwd(t_data *data);
void	run_export(t_data *data);
void	run_export_only(t_data *data);
void	run_env(t_data *data);
void	run_unset(t_data *data);
void	run_exit(t_data *data, int x);

//envp
void	env_setup(t_data *data, char **envp);
t_env	*search_env(t_data *data, char *str);
void	env_to_arr(t_data *data);
int		ft_envsize(t_env *lst);
void	update_env(t_data *data);

// redirects fd
void	redir_hd_fd(t_data *data, int x);
void	redir_in_fd(t_data *data, int x);
void	redir_out_fd(t_data *data, int x);
void	redir_append_fd(t_data *data, int x);

// redirect
void	redirect(t_data *data, int x);
int		is_redir(t_data *data, int x, char *str);

//child
void	child_process(t_data *data, int x);

// signals
int		set_signal_handler(int signum, void (*handler)(int));
int		set_signal_handler(int signum, void (*handler)(int));
void	toggle_input(int mode);
void	heredoc_handler(int sig);
void	signal_setup(int mode);
void	sig_handler(int sig);
void	toggle_input(int mode);
void	rl_replace_line(const char *text, int clear_undo);

//Input checking
int		prompt_check(t_data *data, char *line);
char	syntax_check(char *line);
char	quotes_check(char *line);

// Parsing
void	space_replace(char *str);
void	pipe_replace(char *str);
int		parse_start(t_data *data, char *line);
int		pipe_scans(char *line);
int		calcu_redir(char *str);
int		extract_redir(char *str, char **redir, int i);
int		extract_cmd(char **temp, int i);
int		check_token(t_data *data);
char	quote_finder(char c, char q);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**prompt_prep(char *line, int opt);

//expand
char	*check_expand(char *s, t_data *d);
char	*expand_key(t_data *data, char *key);

// Remove Quotes
void	ft_removequotes(char *str);
void	ft_unquotes(t_token *token);

//here_doc
int		check_heredoc(t_token *t);
int		here_doc(t_data *data);

//pipes
void	create_pipes(t_data *data);
void	create_forks(t_data *data);
void	close_pipes(t_data *data);
void	redirect(t_data *data, int x);
void	redirect_builtin(t_data *data, int x);
void	restore_stdio(t_data *data, int x);

//basic utils
char	*find_end(char *str);
int		ft_arr_len(char **array);
int		ft_isspace(char c);
int		ft_isredir(char c);
int		ft_ismeta(char c);
int		ft_isquote(char c);
int		ft_strcmp(char *s1, char *s2);
int		skip_whitespace(char *str, int i);
int		skip_whitespace2(char *str, int i);

//safe mem allocation
void	*ft_safe_calloc(size_t count, size_t size);
void	*ft_safe_malloc(size_t size);
void	safe_dup2(int fd1, int fd2);
char	*ft_safe_substr(const char *s, unsigned int start, size_t len);
int		safe_dup(int fd);

//errors
void	error_msg(char *msg);
void	error(t_data *data, t_error code, int e);
void	error_var(t_data *data, t_error code, char *var, int e);
void	error_cd(t_data *data, t_error code, char *var, char c);

//memory cleaning
void	free_data_all(t_data *data, int type);
void	ft_free_arr(char **arr);
void	ft_free_tri(char ***tri);
void	ft_free_token(t_data *s_data);
void	free_single_token(t_data *data, int i);
void	ft_free_before_loop(t_data *data);

#endif
