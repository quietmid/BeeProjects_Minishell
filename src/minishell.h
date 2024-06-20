
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

typedef enum e_token_type
{
	NO_TOKEN, // 0
	PIPE_TOKEN, // | 1
	HERE_DOC_TOKEN, // << 2 
	REDIR_IN_TOKEN, // < 3
	REDIR_OUT_TOKEN, // > 4 
	REDIR_APP_OUT_TOKEN, // >> 5
	STRING_TOKEN, // 6
	DOLLAR_TOKEN, // $ 7
	INFILE_TOKEN, // 8
	OUTFILE_TOKEN, // 9
	OUTFILE_TRUNC_TOKEN, // 10
	DELIM_TOKEN, // 11
}	t_token_type;

typedef struct s_token
{
	int				idx;
	char			**cmd;
	char			***redir;
	int				in;
	int				out;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	pid_t			*pid;
	int				**pipe;
	char			**line; //test input delete later
	char			***argv;
	char			**paths;
	char			*path_cmd;
	int				cmd_count;
	char			*pwd;
	char			*oldpwd;
	char			**env_arr;
	int				status;
	t_env			*env;
	t_token			*token;
	int				arr_len;
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
t_env	*create_envnode(char *envp);

// signals
void	heredoc_handler(int sig);
void	signal_setup(int mode);
void	sig_handler(int sig);
void	rl_replace_line(const char *text, int clear_undo);

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
//int		parse_start(char *line);
int		pipe_scans(char *line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char 	**prompt_prep(char *line, int opt);
//t_token_type deter_token_type(char *input);
t_token assign_token(char *input, int i);

//pipes
void	create_pipes(t_data *data);
void	create_forks(t_data *data);
char	*find_path_cmd(t_data *data);

//basic utils
char	**ft_arr_copy(char **arr);
int		ft_arr_len(char **array);
void	ft_free_arr(char **arr);
void	ft_arr_print(char **arr);
int		ft_envsize(t_env *lst);
int 	ft_isspace(char c);
int 	ft_isredir(char c);
int 	empty_line(char *input);
int 	ft_ismeta(char c);
char 	*find_end(char *str);
int	ft_strcmp(char *s1, char *s2);

//safe mem allocation
void	*ft_safe_calloc(size_t count, size_t size);
void	*ft_safe_malloc(size_t size);

//errors
void	error_msg(char *msg);
void	error_arr_free(char *msg, char **str);
char	*ft_safe_substr(const char *s, unsigned int start, size_t len);

#endif