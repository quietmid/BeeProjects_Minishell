/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:54 by jlu               #+#    #+#             */
/*   Updated: 2024/06/27 17:01:52 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
will we ever have the siutation were there will be two pairs of double quotes
void    check_expand(char *input)
    {
        int = s_quote;
        char *str;

        str = input;
        s_quote = 0;
        while (*str)
        {
            if (*str == 39)
                s_quote += 1;
            if (*str == 36 && s_quote % 2 == 0)
                
        }
    }
*/

char *expanding(char *str, int start)
{
    char *result;
    char *temp;
    int exp_len; //the len of the expansion
    int t_len; // the total len of expansion plus the remaining of the str
    /*
    from the start + 1 all the way to the space we find what the variable is named after
    we search the env for the same
    if there is, we save that in temp and find the length of the temp and the current str
    together that's the t_len
    now from the start, we need to insert the temp.
    */

    return (result);
}
// takes in the token and check if there is a $ and if there are quotes
/*
    if the first quote is d_q, then even if the $ is in s_q, it WILL expand
    if the first quote is s_q, then it won't expand 
*/
void check_expand(t_token *token)
{
    int i;
    int x;
    char q; // " = 34 & ' = 39

    q = 0;
    i = 0;
    while (token->redir[i])
    {
        x = 0;
        while (token->redir[i][1][x])
        {
            if (!q && ft_isquote(token->redir[i][1][x]))
                q = token->redir[i][1][x];
            else if (token->redir[i][1][x] == q)
                q = 0;
            if (token->redir[i][1][x] == 36 && q == 34)
                //expanding
            x++;
        }
        i++;
    }
    i = 0;
    while (token->cmd[i])
    {
        x = 0;
        while (token->cmd[i][x])
        {
            if (!q && ft_isquote(token->cmd[i][x]))
                q = token->cmd[i][x];
            else if (token->cmd[i][x] == q)
                q = 0;
            if (token->cmd[i][x] == 36 && q == 34)
                //expanding
            x++;
        }
        i++;
    }

}
