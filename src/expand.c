/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:54:35 by jlu               #+#    #+#             */
/*   Updated: 2024/07/19 18:55:34 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strcpy2(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

static char	*find_key(t_data *d, char *s, int i)
{
	int		start;
	char	*value;
	char	*key;

	start = i;
	if (s[i] == '?')
	{
		value = ft_itoa(WEXITSTATUS(d->status));
		return (value);
	}
	else
	{
		while (!ft_isspace(s[i]) && (isalpha(s[i]) || s[i] == '_'))
			i++;
		key = (char *)ft_safe_malloc(sizeof(char) * (i - start + 1));
		ft_strlcpy(key, s + start, i - start + 1);
		value = expand_key(d, key);
	}
	if (!value)
		value = ft_strdup("");
	free (key);
	return (value);
}

static char	*expand_line(t_data *d, char *s, int i)
{
	char	*value;
	char	*line;
	int		line_len;
	int		x;
	size_t	st;

	value = find_key(d, s, i);
	st = i;
	while (!ft_isspace(s[st]) && (isalpha(s[st]) || s[st] == '_'))
		st++;
	if (s[i] == '?')
		x = 0;
	else
		x = ft_strlen(s) - st;
	line_len = ft_strlen(value) + i + x + 1;
	if (x == 0 && i == 1)
		return (value);
	line = (char *)ft_safe_malloc(sizeof(char) * line_len);
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
	char	q;

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
				error_msg("expand malloc failed");
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
