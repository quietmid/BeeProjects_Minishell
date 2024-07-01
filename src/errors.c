
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
	(void)data;
	if (code == e_malloc)
	{
		// free all function
		ft_putstr_fd(ERR_MALLOC, 2);
	}
	if (code == e_pipe)
	{
		// free all function
		ft_putstr_fd(ERR_PIPE, 2);
	}
	if (code == e_fork)
	{
		// free all function
		ft_putstr_fd(ERR_FORK, 2);
	}
	exit (e);

	
}
