/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:54 by jlu               #+#    #+#             */
/*   Updated: 2024/07/04 14:07:43 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *add_quotes(char *s)
{
    char *new_s;

    //debug
    printf("before str len: %ld\n", ft_strlen(s));
    //debug
    new_s = ft_safe_calloc(1, sizeof(char));
    if (s[0] == 31)
        s = ft_safe_substr(s, 1, ft_strlen(s) - 2);
    //debug
    printf("%s\n", s);
    printf("after str len: %ld\n", ft_strlen(s));
    //debug
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
    printf("1st-str len: %d\n", len);
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
// takes in the string and s for the location of the $ in the string
char *expanding(t_data *data, char *str, int s)
{
    char *result;
    char *temp;
    int found;
    size_t i;
    t_env *e;

    result = 0;
    found = 0;
    i = s + 1;
    while (!ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i])
        i++;
    temp = ft_safe_substr(str, s + 1, i - s - 1);
    e = data->env;
    while (e)
    {
        if (ft_strcmp(temp, e->key) == 0)
        {
            temp = e->value;
            found = 1;
        }
        e = e->next;
    }
    if (found == 1)
    {
        printf("value: %s\n", temp);
        printf("value len: %ld\n", ft_strlen(temp));
        temp = check_meta(temp);
    }
    // IF found! need to check if temp has a special char
    if (found == 0)
        temp = ft_strdup("");
    if (s == 0 && found == 1)
        return (temp);
    else if (found == 1) // copy str
    {
        result = malloc(sizeof(char) * (ft_strlen(str) - i + ft_strlen(temp)));
        ft_strlcpy(result, str, s + 1);
        if (temp)
            result = ft_strjoin(result, temp);
        str = ft_safe_substr(str, i, ft_strlen(str) - i);
        result = ft_strjoin(result, str);
    }
    if (s == 0 && found == 0 && !result)
        return (temp);
    return (result);
}
// takes in the token and check if there is a $ and if there are quotes
/*
    if the first quote is d_q, then even if the $ is in s_q, it WILL expand
    if the first quote is s_q, then it won't expand 
*/
char  *check_expand(char *s, t_data *d)
{
    size_t i;
    char q; // " = 34 & ' = 39

    q = 0;
    i = 0;
    while (i < ft_strlen(s))
    {
        if (!q && ft_isquote(s[i]))
             q = s[i];
        else if (s[i] == q)
            q = 0;
        if ((s[i] == 36 && ((s[i + 1] == '_') || ft_isalpha(s[i + 1]) || ft_isalnum(s[i + 1])) && (q == 34 || q == 0)))
        {
            s = expanding(d, s, i);
            printf("new string is: %s\n", s);
        }
        i++;
    }
    return (s);
}

