/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:21:34 by jlu               #+#    #+#             */
/*   Updated: 2024/07/18 22:02:32 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		error_msg("dup");
	return (new_fd);
}

void	safe_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error_msg("dup2");
	close(fd1);
}
