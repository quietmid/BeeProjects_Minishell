
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

void	print_errors(char *errmsg, char *str, char c)
{
	ft_putstr_fd(errmsg, 2);
	if (c)
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd(" newline", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(" \"\n", 2);
}

void	error(t_data *data, t_error code, int e)
{
	//(void)data; //uncomment when free all function is done
	// free all function
	(void)data;
	if (code == XMALLOC)
		ft_putstr_fd(ERR_MALLOC, 2);
	if (code == XPIPE)
		ft_putstr_fd(ERR_PIPE, 2);
	if (code == XFORK)
		ft_putstr_fd(ERR_FORK, 2);
	if (code == XEXEC)
		ft_putstr_fd(ERR_EXEC, 2);
	if (code == XHD)
		ft_putstr_fd(ERR_HD, 2);
	exit (e);

}

void error_cd(t_data *data, t_error code, char *var, char c)
{
	(void)data;
	ft_putstr_fd("minishell-8.8$: ", 2);
	if (code == XCD)
	{
		ft_putstr_fd("cd: ", 2);
		perror(var);
	}
	else if (code == XCDHOME)
		ft_putendl_fd(ERR_HOME, 2);
	else if (code == XCDOLDPWD)
		ft_putendl_fd(ERR_OLDPWD, 2);
	else if (code == XSYNTAX)
		print_errors(ERR_SYNTAX, NULL, c);
}

void	error_var(t_data *data, t_error code, char *var, int e)
{
	// //(void)data; //uncomment when free all function is done
	// (void)data;
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
		if (code == XNOFILE || code == XDIR)
		{
			ft_putstr_fd(var, 2);
			ft_putstr_fd(": ", 2);
			if (code == XNOFILE)
				ft_putendl_fd(ERR_NOFILE, 2);
			else if (code == XDIR)
				ft_putendl_fd(ERR_DIR, 2);
		}
		else
			perror(var);
	}
	// free_all(data);
	ft_free_token(data);
	ft_free_before_loop(data);
	exit (e);
}
