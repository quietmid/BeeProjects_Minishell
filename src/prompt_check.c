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

// add the error function that prints the char that's the syntax issue
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
        if (line[i] == '|' && line[i + 1] == '|')
            return (0);
        if (ft_isredir(line[i]) && ft_isspace(line[i + 1]))
        {
            while (ft_isspace(line[i]))
                i++;
            if (!line[i] || ft_isredir(line[i]) || line[i] == '|')
                return (0);
        }
        i++;
    }
    return (1);
}

int prompt_check(char *line)
{
    if (!quotes_check(line))
        return (0);
    if (!syntax_check(line))
        return (0);
    return (1);
}