/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:03:33 by jlu               #+#    #+#             */
/*   Updated: 2024/07/25 17:13:03 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_quotes(char *s)
{
	char	*new_s;

	new_s = ft_safe_calloc(1, sizeof(char));
	if (s[0] == 31)
		s = ft_safe_substr(s, 1, ft_strlen(s) - 2);
	new_s = ft_strjoin("\"", s);
	new_s = ft_strjoin(new_s, "\"");
	return (new_s);
}

char	*check_meta(char *s)
{
	int		i;
	char	*new_s;

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

char	*expand_key(t_data *data, char *key)
{
	t_env	*e;

	e = data->env;
	while (e)
	{
		if (ft_strcmp(key, e->key) == 0)
		{
			key = ft_strdup(e->value);
			return (key);
		}
		e = e->next;
	}
	return (NULL);
}

int	expandable_check(char *s, int i)
{
	if (s[i + 1] && ft_isexp(s[i + 1]))
	{
		if (ft_isquote(s[i + 1]) && i - 1 >= 0)
		{
			if (ft_isquote(s[i - 1]))
				return (0);
		}
	}
	return (1);
}
