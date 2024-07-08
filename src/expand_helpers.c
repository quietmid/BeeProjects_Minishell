/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:41:01 by jlu               #+#    #+#             */
/*   Updated: 2024/07/08 20:42:54 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *add_quotes(char *s)
{
    char *new_s;

    new_s = ft_safe_calloc(1, sizeof(char));
    if (s[0] == 31)
        s = ft_safe_substr(s, 1, ft_strlen(s) - 2);

    new_s = ft_strjoin("\"", s);
    new_s = ft_strjoin(new_s, "\"");
    return (new_s);
}

char *check_meta(char *s)
{
    int i;
    int len;
    char *new_s;

    len = ft_strlen(s);
    new_s = NULL;
    i = 0;
    while (s[i])
    {
        if (ft_ismeta(s[i]) || ft_isquote(s[i]))
        {
            new_s = add_quotes(s);
            break ;
        }
        i++;
    }
    if (new_s)
        return (new_s);
    else
        return (s);
}

void* expand_key(t_data *data, char *temp, int *found)
{
    t_env *e;

    e = data->env;
    while (e)
    {
        if (ft_strcmp(temp, e->key) == 0)
        {
            temp = e->value;
            *found = 1;
            return (temp);
        }
        e = e->next;
    }
    return (NULL);
}