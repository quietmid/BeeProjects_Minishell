/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:36:36 by jlu               #+#    #+#             */
/*   Updated: 2024/07/18 20:32:21 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	while (i < n)
	{
		*dest++ = *src++;
		i++;
	}
	*dest = '\0';
}
