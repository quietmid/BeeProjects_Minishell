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
char syntax_check(char *line)
{
    int i;
    int len;
    char c;

    len = ft_strlen(line) - 1;
    i = 0;
    if (line[0] == '|')
        return (line[0]);
    if (ft_ismeta(line[len]))
        return (line[len]);
    while (line[i])
    {
        if (line[i] == '|' && line[i + 1] == '|')
            return (line[i]);
        if (ft_isredir(line[i]) || line[i] == '|')
        {
            c = line[i++];
            while (ft_isspace(line[i]))
                i++;
            if (line[i] == '\0')
                return (c);
            else if (ft_isredir(line[i]) || line[i] == '|')
                return (line[i]);
        }
        i++;
    }
    return (0);
}

int prompt_check(char *line)
{
    char c;

    c = 0;
    if (!quotes_check(line))
    {
        printf("im here quotes check\n");
        return (0);
    }
    c = syntax_check(line);
    if (c != 0)
    {
        printf("im here syntax check\n");
        return (0);
    }
    return (1);
}