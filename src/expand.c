/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:54 by jlu               #+#    #+#             */
/*   Updated: 2024/06/24 15:43:35 by jlu              ###   ########.fr       */
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
t_token check_expand(t_token token)
{
    int i;
    int x;

    i = 0;
    while (token.redir[i])
    {
        x = 0;
        while (token.redir[i][1][x])
        {
            if (token.redir[i][1][x] == 39) // need to check if its just the first quotes that matters
                break ;
            if (token.redir[i][1][x] == 36)
                //expanding
            x++;
        }
        i++;
    }
    i = 0;
    while (token.cmd[i])
    {
        x = 0;
        while (token.cmd[i][x])
        {
            if (token.cmd[i][x] == 39) // need to check if its just the first quotes that matters
                break ;
            if (token.cmd[i][x] == 36)
                //expanding
        }
        i++;
    }

}
