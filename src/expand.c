/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:09:54 by jlu               #+#    #+#             */
/*   Updated: 2024/07/08 20:42:59 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_help(char *str, char *temp, int s, int i, int found)
{
    char *result;

    result = ft_safe_malloc(sizeof(char) * (ft_strlen(str) - i + ft_strlen(temp)));
    ft_strlcpy(result, str, s + 1);
    if (found)
        result = ft_strjoin(result, temp);
    str = ft_safe_substr(str, i, ft_strlen(str) - i);
    result = ft_strjoin(result, str);
    return (result);
}
// takes in the string and s for the location of the $ in the string
char *expanding(t_data *data, char *str, int s)
{
    char *result;
    char *temp;
    int found;
    size_t i;

    result = 0;
    found = 0;
    i = s + 1;
    while (!ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '$' && str[i])
        i++;
    temp = ft_safe_substr(str, s + 1, i - s - 1);
    temp = (char *)expand_key(data, temp, &found);
    if (found == 1)
        temp = check_meta(temp);
    else
        temp = ft_strdup("");
    if (s > 0)
        result = expand_help(str, temp, s, i, found);
    if (s == 0)
        return (temp);
    return (result);
}

char *expand_errcode(t_data *data, char *str, int s)
{
    char *result;
    char *err_code;
    int len;
    t_data *tmp; //delete

    tmp = data; // delete
    len = ft_strlen(str);
    if (len == 2)
        result = ft_safe_substr("echo ", 0, 5);
    else
    {
        result = ft_safe_malloc(sizeof(char) * (len - 2));
        ft_strlcpy(result, str, s + 1);
    }
    err_code = ft_itoa(2); //data->error_code
    result = ft_strjoin(result, err_code);
    if (len > (s + 2))
        str = ft_safe_substr(str, s + 2, len - s - 2);
    else
        str = ft_strdup("");
    result = ft_strjoin(result, str);
    return (result);
}

char *easy_expanding(t_data *data, char *str, int s)
{
    char *result;
    int len;
    t_data *temp;

    temp = data;
    if (s == 0 && str[s + 1] != '?')
        result = ft_strdup("");
    len = ft_strlen(str);
    result = ft_safe_malloc(sizeof(char) * (len - 2));
    if (s > 0)
        ft_strlcpy(result, str, s + 1);
    if (len > (s + 2))
        str = ft_safe_substr(str, s + 2, len - s - 2);
    else
        str = ft_strdup("");
    result = ft_strjoin(result, str);
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
    size_t len;
    char q; // " = 34 & ' = 39

    q = 0;
    i = 0;
    len = ft_strlen(s);
    while (i < len)
    {
        if (!q && ft_isquote(s[i]))
            q = s[i];
        else if (s[i] == q)
            q = 0;
        if (s[i] == 36 && s[i + 1] =='?' && (q == 34 || q == 0))
            s = expand_errcode(d, s, i);
        if ((s[i] == 36 && ((s[i + 1] == '_') || ft_isalpha(s[i + 1])) && (q == 34 || q == 0)))
            s = expanding(d, s, i);
        if ((s[i] == 36 && !ft_isspace(s[i + 1]) && (q == 34 || q == 0)))
            s = easy_expanding(d, s, i);
        len = ft_strlen(s);
        i++;
    }
    return (s);
}

