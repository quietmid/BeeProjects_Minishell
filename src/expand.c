/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/19 14:32:44 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static size_t	ft_strlcpy2(char *dest, const char *src, size_t destsize)
// {
// 	size_t	i;
// 	size_t	srcsize;

// 	i = 0;
// 	srcsize = ft_strlen((char *)src);
// 	if (destsize == 0)
// 		return (srcsize);
// 	while (i < (destsize - 1) && src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (srcsize);
// }

static void	ft_strcpy2(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

static char	*find_key(t_data *d, char *str, int i)
{
	int		start;
	char	*value;
	char	*key;

	start = i;
	if (str[i] == '?')
	{
		value = ft_itoa(WEXITSTATUS(d->status));
		return (value);
	}
	else
	{
		while (!ft_isspace(str[i]) && !ft_isquote(str[i])
			&& str[i] != '$' && str[i] != '?' && str[i])
			i++;
		key = (char *)ft_safe_malloc(sizeof(char) * (i - start + 1));
		ft_strlcpy(key, str + start, i - start + 1);
		value = expand_key(d, key);
	}
	if (!value)
		value = ft_strdup("");
	free (key);
	return (value);
}

static char	*expand_line(t_data *d, char *s, int i) // $??
{
	char	*value;
	char	*line;
	int		line_len;
	int		x;
	size_t	st;

	value = find_key(d, s, i);
	st = i;
	while (!ft_isspace(s[st]) && !ft_isquote(s[st]) && s[st] != '$'
		&& s[st] != '?' && s[st])
		st++;
	if (st == ft_strlen(s))
		x = 0;
	else
		x = ft_strlen(s) - i;
	line_len = ft_strlen(value) + i + x;
	if (x == 0 && i == 1)
		return (value);
	line = (char *)ft_safe_malloc(sizeof(char) * line_len);
	if (i != 1)
		ft_strlcpy(line, s, i);
	ft_strcpy2(line + i - 1, value);
	if (x > 0)
		ft_strcpy2(line + i + ft_strlen(value) - 1, s + st);
	free (value);
	return (line);
}

char	*check_expand(char *s, t_data *d)
{
	char	*new_line;
	int		i;
	char	q;// " = 34 & ' = 39

	i = 0;
	q = 0;
	new_line = NULL;
	while (s[i])
	{
		q = quote_finder(s[i], q);
		if (s[i] == 36 && s[i + 1] && !ft_isspace(s[i + 1])
			&& s[i + 1] != 36 && (q == 34 || !q))
		{
			new_line = expand_line(d, s, i + 1);
			if (!new_line)
			{
				ft_putendl_fd("expand failed", 2);
				free(s);
				return (NULL);
			}
			free(s);
			s = ft_strdup(new_line);
			i = 0;
		}
		else
			i++;
	}
	free(new_line);
	return (s);
}
