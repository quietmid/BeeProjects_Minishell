
#include "minishell.h"

// char *ft_removequotes(char *str)
// {
//     int len;
//     char *new;

//     len = ft_strlen(str);
//     new = ft_safe_malloc(sizeof(char) * len - 1);
//     new = ft_safe_substr(str, 1, len - 2);
//     return (new);
// }

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
now loops through the array of strings and check the first idx, if that's a quote, we remove that and remove the last one. We can replace it with 31?
*/
void    ft_unquotes(t_token *t)
{
    /*
        take in each token, loop through each redir/cmd and check if the [0] is a quote then we remove them.
    */
    int i;
    int x;

    i = 0;
    // printf("redir len: %d\n", t->redir_len);
    while (i < t->redir_len)
    {
        if (ft_isquote(t->redir[i][0][0]))
            ft_removequotes(t->redir[i][0]);
        if (ft_isquote(t->redir[i][1][0]))
            ft_removequotes(t->redir[i][1]);
        i++;
    }
    i = 0;
    while (i < t->cmd_len)
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
        i++;
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
