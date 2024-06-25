#include "minishell.h"

int	quotes_check(char *line)
{
	char q;

	q = 0;
	while (*line)
	{
		if (!q && ft_isquote(*line))
			q = *line;
		else if (*line == q)
			q = 0;
		line++;
	}
	if (q == 0)
		return (1);
	print_errors(ERR_QUOTES);
	return (0);
}

int syntax_check(char *line)
{
    int i;
    int len;

    len = ft_strlen(line) - 1;
    i = 0;
    if (line[0] == '|')
        return (0);
    if (ft_ismeta(line[len]))
        return (0);
    while (line[i])
    {
        
    }
    print_errors(ERR_SYNTAX)
    return (0);
}

int prompt_check(char *line)
{
    if (!quotes_check(line))
        return (0);
    if (!syntax_check(line))
        return (0);
    return (1);
}