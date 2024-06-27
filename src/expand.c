/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:54 by jlu               #+#    #+#             */
/*   Updated: 2024/06/27 19:17:38 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// takes in the string and s for the location of the $ in the string
char *expanding(char *str, int s)
{
    char *result;
    char *temp;
    int exp_len; //the len of the expansion
    int t_len; // the total len of expansion plus the remaining of the str
    int i;
    /*
    maybe I should split it by space
    from the start + 1 all the way to the space we find what the variable is named after
    we search the env for the same
    if there is, we save that in temp and find the length of the temp and the current str
    together that's the t_len
    now from the start, we need to insert the temp.
    */
    i = 0;
    if (str[s + 1] == '_' || ft_isalpha(str[s + 1])) //check the next char
    {
        while (!ft_isspace(str[s]))
        {
            s++;
            i++;
        }
    }
        

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
