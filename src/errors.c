
#include "minishell.h"

// ALPHA error_msg
void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	error_arr_free(char *msg, char **str)
{
	ft_free_arr(str);
	printf("%s\n", msg);
	exit (EXIT_FAILURE);
}

void	print_errors(char *errmsg, char *syntax)
{
	ft_putstr_fd("minishell-8.8$ ", 2);
	ft_putstr_fd(errmsg, 2);
	if (syntax)
	{
		ft_putstr_fd(syntax, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}

void	error(t_data *data, t_error code, int e)
{
	(void)data; //uncomment when free all function is done
	// free all function
	if (code == XMALLOC)
		ft_putstr_fd(ERR_MALLOC, 2);
	if (code == XPIPE)
		ft_putstr_fd(ERR_PIPE, 2);
	if (code == XFORK)
		ft_putstr_fd(ERR_FORK, 2);
	if (code == XEXEC)
		ft_putstr_fd(ERR_EXEC, 2);
	exit (e);
}

void error_cd(t_data *data, t_error code, char *var)
{
	(void)data;
	ft_putstr_fd("minishell-8.8$", 2);
	ft_putstr_fd(": ", 2);
	if (code == XCD)
	{
		ft_putstr_fd("cd: ", 2);
		perror(var);
	}
	else if (code == XCDHOME)
		ft_putendl_fd(ERR_HOME, 2);
	else if (code == XCDOLDPWD)
		ft_putendl_fd(ERR_OLDPWD, 2);
}

void	error_var(t_data *data, t_error code, char *var, int e)
{
	(void)data; //uncomment when free all function is done
	// free all function
	if (code == XCMD)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(ERR_CMD, 2);
	}
	else
	{
		ft_putstr_fd("minishell-8.8$", 2);
		ft_putstr_fd(": ", 2);
		if (code == XNOFILE)
		{
			ft_putstr_fd(var, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(ERR_NOFILE, 2);
		}
		else
			perror(var);
	}
	exit (e);
}
