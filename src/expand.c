/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/17 16:48:06 by jlu              ###   ########.fr       */
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
    char *res;
    char *tmp;
    int len;
  
    len = ft_strlen(str);
    if (len == 2)
        tmp = ft_safe_substr("echo ", 0, 5);
    else
    {
        tmp = ft_safe_malloc(sizeof(char) * (len - 2));
        ft_strlcpy(tmp, str, s + 1);
    }
    err_code = ft_itoa(WEXITSTATUS(data->status)); //data->status!!!
    res = ft_strjoin(tmp, err_code);
    free(tmp);
    if (len > (s + 2))
        str = ft_safe_substr(str, s + 2, len - s - 2);
    else
        str = ft_strdup("");
    result = ft_strjoin(res, str);
    free(res);
    free(err_code);
    free(str);
    return (result);
}

char *easy_expanding(char *str, int s)
{
    char *result;
    int len;
    
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

char  *check_expand(char *s, t_data *d)
{
    size_t i;
    size_t len;
    char q; // " = 34 & ' = 39
    char *tmp;

    q = 0;
    i = 0;
    len = ft_strlen(s);
    while (i < len)
    {
        tmp = s;
        q = quote_finder(s[i], q);
        if (s[i] == 36 && s[i + 1] =='?' && (q == 34 || q == 0))
            s = expand_errcode(d, tmp, i);
        else if ((s[i] == 36 && ((s[i + 1] == '_') || ft_isalpha(s[i + 1])) && (q == 34 || q == 0)))
            s = expanding(d, tmp, i);
        else if ((s[i] == 36 && !ft_isspace(s[i + 1]) && (q == 34 || q == 0)))
            s = easy_expanding(tmp, i);
        len = ft_strlen(s);
        i++;
    }
    return (s);
}
