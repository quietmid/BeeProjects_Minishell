
#include "minishell.h"

// 34 = " , 39 = '
int	ft_isquote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

void    ft_removequotes(char *str)
{
    int i;
    char q;

    i = 0;
    q = 0;
    while (str[i])
    {
        if (!q && ft_isquote(str[i]))
        {
            q = str[i];
            str[i] = 31;
        }
        else if (str[i] == q)
        {
            q = 0;
            str[i] = 31;
        }
        i++;
    }
}
/*
    take in each token, loop through each redir/cmd and check if the [0] is a quote then we remove them.
*/
void    ft_unquotes(t_token *t)
{
    int i;
    int x;

    i = -1;
    while (++i < t->redir_len)
    {
        if (ft_isquote(t->redir[i][0][0]))
            ft_removequotes(t->redir[i][0]);
        if (ft_isquote(t->redir[i][1][0]))
            ft_removequotes(t->redir[i][1]);
    }
    i = -1;
    while (++i < t->cmd_len)
    {
        x = 0;
        while (t->cmd[i][x])
        {
            if (ft_isquote(t->cmd[i][x]))
            {
                ft_removequotes(t->cmd[i]);
                break ;
            }
            x++;
        }
    }
}

// int main()
// {
//     char str[] = "\"happy 'wrold' tree\"";
    
//     printf("here\n");
//     // str = ft_removequotes(str);
// 	ft_removequotes(str);
//     printf("%s\n", str);
//     return (0);
// }
