
#include "minishell.h"

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