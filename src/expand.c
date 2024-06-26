/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:54 by jlu               #+#    #+#             */
/*   Updated: 2024/07/01 17:27:54 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// takes in the string and s for the location of the $ in the string
char *expanding(t_data *data, char *str, int s)
{
    char *result;
    char *temp;
    // int exp_len; //the len of the expansion
    // int t_len; // the total len of expansion plus the remaining of the str
    int i;
    int found;

    // i = s;
    found = 0;
    printf("s idx: %d\n", s);
    printf("expand string: %s\n", str);
    if (str[s + 1] == '_' || ft_isalpha(str[s + 1])) //check the next char
    {
        i = s + 1;
        while (!ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i])
            i++;
        temp = ft_safe_substr(str, s + 1, i - s);
        printf("key: %s\n", temp);
        while (data->env)
        {
            if (ft_strcmp(temp, data->env->key) == 0)
            {
                temp = data->env->value;
                found = 1;
            }
            data->env = data->env->next;
        }
    }
    if (found == 0)
    {
        printf("nothing found!\n");
        temp = ft_strdup("");
    }
    printf("temp string2: %s\n", temp);
    result = malloc(sizeof(char) * (ft_strlen(str) - i + ft_strlen(temp)));
    ft_strlcpy(result, str, s);
    if (!result)
        return ("");
    result = ft_strjoin(result, temp);
    str = ft_safe_substr(str, i, ft_strlen(str) - i);
    result = ft_strjoin(result, str);
    return (result);
}
// takes in the token and check if there is a $ and if there are quotes
/*
    if the first quote is d_q, then even if the $ is in s_q, it WILL expand
    if the first quote is s_q, then it won't expand 
*/
void check_expand(t_token *token, t_data *data)
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
            if (token->redir[i][1][x] == 36 && (q == 34 || q == 0))
                token->redir[i][1] = expanding(data, token->redir[i][1], x);
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
            if (token->cmd[i][x] == 36 && (q == 34 || q == 0))
                token->cmd[i] = expanding(data, token->cmd[i], x);
            x++;
        }
        i++;
    }
}
