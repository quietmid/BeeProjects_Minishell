/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:16:06 by jlu               #+#    #+#             */
/*   Updated: 2024/06/27 18:09:08 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int n)
{
	if (n >= 'A' && n <= 'Z')
	{
		return (1);
	}
	else if (n >= 'a' && n <= 'z')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
