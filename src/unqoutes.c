
#include "minishell.h"


void    ft_removequotes(char *str)
{
    int end;

    end = ft_strlen(str) - 1;
    str[0] = 31;
    str[end] = 31;
}
/*
now loops through the array of strings and check the first idx, if that's a quote, we remove that and remove the last one. We can replace it with 31?
*/
void    ft_unqotes()
{
    /*
        take in each token, loop through each redir/cmd and check if the [0] is a quote then we remove them.
    */
    int i;

    i = 0;
    while (i < token->redir_len)
    {
        if (ft_isquote(token->redir[i][0][0]))
            //ft_removequotes();
        if (ft_isquote(token->redir[i][1][0]))
            //ft_removequotes();
        i++;
    }
    i = 0;
    while (i < token->cmd_len)
    {
        if (ft_isquote(token->cmd[i][0]))
            //ft_removequotes();
        i++;
    }
}
