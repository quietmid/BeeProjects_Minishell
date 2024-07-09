
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
#include <sys/stat.h> //stat
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>


# define TRUE 1
# define FALSE 0


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

// typedef enum e_token_type
// {
// 	NO_TOKEN, // 0
// 	PIPE_TOKEN, // | 1
// 	HERE_DOC_TOKEN, // << 2 
// 	REDIR_IN_TOKEN, // < 3
// 	REDIR_OUT_TOKEN, // > 4 
// 	REDIR_APP_OUT_TOKEN, // >> 5
// 	STRING_TOKEN, // 6
// 	DOLLAR_TOKEN, // $ 7
// 	INFILE_TOKEN, // 8
// 	OUTFILE_TOKEN, // 9
// 	OUTFILE_TRUNC_TOKEN, // 10
// 	DELIM_TOKEN, // 11
// }	t_token_type;

typedef struct s_token
{
	int				idx;
	int				redir_len;
	int				cmd_len;
	int				in;
	int				out;
	int				hd;
	char			**cmd; // free
	char			***redir; // free 

}					t_token;

typedef struct s_env
{
	char			*key; // free 
	char			*value; //free
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	int				parent_in;
	int				parent_out;
	int				*pid; // free
	int				**pipe; // free
	int				status;
	int				arr_len;
	int				hd; //here_doc
	int				error_code;
	//char			***argv; // free
	char			**paths; // free
	char			**env_arr; // free
	char			*path_cmd; // free
	int				cmd_count;
	int				pipe_count;
	char			*pwd; // free
	char			*oldpwd; // free
	t_env			*env;
	t_token			*token;
	struct s_parse	*par;
}		t_data;

//functions

//builtin
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data);
void	run_echo(t_data *data);
void	run_cd(t_data *data);
void	run_pwd(t_data *data);
void	run_export(t_data *data);
void	run_env(t_data *data);
void	run_unset(t_data *data);

//envp
void	env_setup(t_data *data, char **envp);
t_env	*search_env(t_data *data, char *str);
void	env_to_arr(t_data *data);
int		ft_envsize(t_env *lst);
void	update_data(t_data *data);
t_env	*create_envnode(t_data *data, char *envp);

// signals
void	heredoc_handler(int sig);
void	signal_setup(int mode);
void	sig_handler(int sig);
void	rl_replace_line(const char *text, int clear_undo);

//Input checking
int 	prompt_check(char *line);
char 	syntax_check(char *line);
int		quotes_check(char *line);

// Parsing
// void	parse(t_data *data, const char *line);
void	space_replace(char *str);
void	pipe_replace(char *str);
//void	assign_token(char *input, t_data *data, int idx);
// void	array_join(t_data *data);
//void	array_join(t_data *data, t_parse *u);
// void	init_token(t_data *data, char **str);
//void	assign_token(char *input, t_data *data, int i);
//int		cmd_len(t_data *data, int i);
int		parse_start(t_data *data, char *line);
int		pipe_scans(char *line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char 	**prompt_prep(char *line, int opt);
// t_token assign_token(char *input, int i);
void	assign_token(char *input, t_token *token);
t_token	init_token(char *str, int i);

//expand
// void check_expand(t_token *token, t_data *data);
// void check_expand(char *s, t_data *d);
char *check_expand(char *s, t_data *d);
char *expanding(t_data *data, char *str, int s);
char *easy_expanding(t_data *data, char *str, int s);
char *check_meta(char *s);
char *add_quotes(char *s);
void* expand_key(t_data *data, char *temp, int *found);

// Remove Quotes
void    ft_removequotes(char *str);
void    ft_unquotes(t_token *token);

//here_doc
int    check_heredoc(t_token *t);
void    here_doc(t_data *data);


//pipes
void	create_pipes(t_data *data);
void	create_forks(t_data *data);
char	*find_path_cmd(t_data *data, int i);
void	close_pipes(t_data *data);
void	redirect(t_data *data, int x);
void	redirect_builtin(t_data *data, int x);
void	restore_stdio(t_data *data, int x);

//basic utils
char	**ft_arr_copy(char **arr);
int		ft_arr_len(char **array);
void	ft_arr_print(char **arr);
int		ft_envsize(t_env *lst);
int 	ft_isspace(char c);
int 	ft_isredir(char c);
int 	ft_ismeta(char c);
int		ft_isquote(char c);
int 	empty_line(char *input);
char 	*find_end(char *str);
int	ft_strcmp(char *s1, char *s2);

//safe mem allocation
void	*ft_safe_calloc(size_t count, size_t size);
void	*ft_safe_malloc(size_t size);
char	*ft_safe_substr(const char *s, unsigned int start, size_t len);

//errors
void	error_msg(char *msg);
void	error_arr_free(char *msg, char **str);
void	print_errors(char *errmsg, char *syntax);
void	error(t_data *data, t_error code, int e);
void	error_var(t_data *data, t_error code, char *var, int e);
void 	error_cd(t_data *data, t_error code, char *var);

//memory cleaning
void 	free_data_all(t_data *data, int type);
void	ft_free_arr(char **arr);
void	ft_free_tri(char ***tri);
void	ft_free_token(t_data *s_data);
void	ft_free_env(t_env *env);

#endif