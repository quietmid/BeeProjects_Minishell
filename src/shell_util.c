/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:36:15 by jlu               #+#    #+#             */
/*   Updated: 2024/05/30 17:11:38 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//error handling functions

char	*find_path(char **envp)
{
	int	i;

	if (!envp || !*envp)
		*envp = "PATH=/bin:/usr/bin";
	i = 0;
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
		if (!*envp)
			return (NULL);
	}
	return (*envp + 5);
}