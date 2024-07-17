/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/17 23:42:44 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// static void v_strcpy(char *dst, const char *src)
// {
// 	while (*src)
// 		*dst++ = *src++;
// 	*dst = '\0';
// }

// char *expand_help(char *str, char *temp, int s, int i, int found)
// {
//     char *result;

//     result = ft_safe_malloc(sizeof(char) * (ft_strlen(str) - i + ft_strlen(temp)));
//     ft_strlcpy(result, str, s + 1);
//     if (found)
//         result = ft_strjoin(result, temp);
//     str = ft_safe_substr(str, i, ft_strlen(str) - i);
//     result = ft_strjoin(result, str);
//     return (result);
// }

// // takes in the string and s for the location of the $ in the string
// char *expanding(t_data *data, char *str, int s)
// {
//     char *result;
//     char *temp;
//     int found;
//     size_t i;

//     result = 0;
//     found = 0;
//     i = s + 1;
//     while (!ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '$' && str[i])
//         i++;
//     temp = ft_safe_substr(str, s + 1, i - s - 1);
//     temp = expand_key(data, temp);
//     if (found == 1)
//         temp = check_meta(temp);
//     else
//         temp = ft_strdup("");
//     if (s > 0)
//         result = expand_help(str, temp, s, i, found);
//     if (s == 0)
//         return (temp);
//     return (result);
// }

// char *expand_errcode(t_data *data, char *str, int s)
// {
//     char *result;
//     char *err_code;
//     int len;

//     result = NULL;
//     len = ft_strlen(str);
//     err_code = ft_itoa(data->status);
//     if (len == 2)
//         return (err_code);
//     ft_strlcpy(result, str, s + 1);
//     v_strcpy((result + ft_strlen(result)), err_code);
//     if (len > s + 2)
//         v_strcpy(result + ft_strlen(result), (str + s + 2));
//     free(err_code);
//     free(str);
//     return (result);
// }
// char *expand_errcode(t_data *data, char *str, int s)
// {
//     char *result;
//     char *err_code;
//     char *res;
//     char *tmp;
//     int len;
  
//     tmp = NULL;
//     len = ft_strlen(str);
//     if (len == 2)
//         printf("%d\n", data->status);
//         // tmp = ft_safe_substr("echo ", 0, 5);
//     else
//     {
//         tmp = ft_safe_malloc(sizeof(char) * (len - 2));
//         ft_strlcpy(tmp, str, s + 1);
//     }
//     err_code = ft_itoa(WEXITSTATUS(data->status)); //data->status!!!
//     res = ft_strjoin(tmp, err_code);
//     free(tmp);
//     if (len > (s + 2))
//         str = ft_safe_substr(str, s + 2, len - s - 2);
//     else
//         str = ft_strdup("");
//     result = ft_strjoin(res, str);
//     free(res);
//     free(err_code);
//     free(str);
//     return (result);
// }

// char *easy_expanding(char *str, int s)
// {
//     char *result;
//     int len;
    
//     if (s == 0 && str[s + 1] != '?')
//         result = ft_strdup("");
//     len = ft_strlen(str);
//     result = ft_safe_malloc(sizeof(char) * (len - 2));
//     if (s > 0)
//         ft_strlcpy(result, str, s + 1);
//     if (len > (s + 2))
//         str = ft_safe_substr(str, s + 2, len - s - 2);
//     else
//         str = ft_strdup("");
//     result = ft_strjoin(result, str);
//     return (result);
// }

// char  *check_expand(char *s, t_data *d)
// {
//     size_t i;
//     char q; // " = 34 & ' = 39
//     char *exp_line;

//     q = 0;
//     i = 0;;
//     exp_line = s;
//     while (s[i])
//     {
//         q = quote_finder(s[i], q);
//         if (s[i] == 36 && s[i + 1] =='?' && (q == 34 || q == 0))
//             exp_line = expand_errcode(d, s, i);
//         else if ((s[i] == 36 && ((s[i + 1] == '_') || ft_isalpha(s[i + 1])) && (q == 34 || q == 0)))
//             exp_line = expanding(d, s, i);
//         else if ((s[i] == 36 && !ft_isspace(s[i + 1]) && (q == 34 || q == 0)))
//             exp_line = easy_expanding(s, i);
//         // free(s);
//         s = ft_strdup(exp_line);
//         i++;
//     }
//     free(exp_line);
//     return (s);
// }

static char  *find_key(t_data *d, char *str, int i)
{
    int start;
    char *value;
    char *key;

    start = i;
    if (str[i + 1] == '?')
    {
        value = ft_itoa(WEXITSTATUS(d->status));
        return (value);
    }
    else
    {
        while (!ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '$' && str[i] != '?' && str[i])
            i++;
        key = (char *)ft_safe_malloc(sizeof(char) * (i - start));
        value = expand_key(d, key);
    }
    if (!value)
        value = ft_strdup("");
    return (value);
}

static char *expand_line(t_data *d, char *s, int i)
{
    char *value;
    char *line;
    int line_len;
    int x;
    int st;

    value = find_key(d, s, i);
    st = i;
    while (!ft_isspace(s[i]) && !ft_isquote(s[i]) && s[i] != '$' && s[i] != '?' && s[i])
        i++;
    if (st != i)
    {
        x = ft_strlen(s) - i;
        while (s[x] != '\0')
            x++;
    }
    else
        x = 0;
    line_len = ft_strlen(value) + st + x;
    if (x == 0 && st == 0)
        return (value);
    line = (char *)ft_safe_malloc(sizeof(char) * line_len + 1);
    if (st != 0)
        ft_strlcpy(line, s, st + 1);
    ft_strlcpy(line + st, value, ft_strlen(value) + 1);
    if (x > 0)
        ft_strlcpy((line + st + ft_strlen(value)), s + i, x + 1);
    line[line_len] = '\0';
    free (value);
    return(line);
}

char  *check_expand(char *s, t_data *d)
{
    char q; // " = 34 & ' = 39
    char *new_line;
    int i;

    i = 0;
    q = 0;
    new_line = NULL;
    while (s[i])
    {
        q = quote_finder(s[i], q);
        if (s[i] == 36 && s[i + 1] && !ft_isspace(s[i + 1]) && s[i + 1] != 36 && (q == 34 || !q))
        {
            new_line = expand_line(d, s, i);
            if (!new_line)
            {
                ft_putendl_fd("expand failed", 2);
                free(s);
                return (NULL);
            }
            // free(s);
            // s = ft_strdup(new_line);
            s = new_line;
            // free (new_line);
        }
        i++;
    }
    return (s);
}
