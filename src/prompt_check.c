#include "minishell.h"

char	quotes_check(char *line)
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
		return (0);
	return (q);
}

// add the error function that prints the char that's the syntax issue

/* if i return an int here, maybe I can use that find the symbols to return in the error msg?*/
char syntax_check(char *line)
{
    int i;
    int len;
    char c;

    len = ft_strlen(line) - 1;
    i = 0;
    if (len == -1)
        return (0);
    if (line[0] == '|')
        return (line[0]);
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
            else if (line[i] == '|')
                return (line[i]);
        }
        i++;
    }
    return (0);
}

int prompt_check(t_data *data, char *line)
{
    char c;

    c = 0;
    c = quotes_check(line);
    if (c)
    {
        error_cd(data, XSYNTAX, NULL, c);
        return (0);
    }
    c = 0;
    c = syntax_check(line);
    if (c)
    {
        error_cd(data, XSYNTAX, NULL, c);
        return (0);
    }
    return (1);
}