
#include "minishell.h"

// ALPHA error_msg
void	error_msg(char *msg)
{
	printf("%s\n", msg);
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
