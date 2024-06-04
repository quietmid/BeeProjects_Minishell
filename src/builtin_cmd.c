/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:55:45 by pbumidan          #+#    #+#             */
/*   Updated: 2024/06/04 15:20:44 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* check validity of echo's -n flag 
*/
int	is_nflag(char *str)
{
	int	x;

	x = 0;
	if (str[x] == '-')
	{
		x++;
		while (str[x])
		{
			if (str[x] != 'n')
				return (FALSE);
			x++;
		}
		return (TRUE);
	}
	return (FALSE);
}

/*
* execute builtin command echo (-n)
*/
void	run_echo(t_data *data)
{
	int	x;
	int	n;
	int	start;

	n = 0;
	if (ft_arrlen(data->line) > 1)
	{
		x = 1;
		start = 1;
		while (data->line[x] && is_nflag(data->line[x]) == TRUE)
		{
			n = 1;
			x++;
			start = x;
		}
		while (data->line[start])
		{
			ft_putstr_fd(data->line[start], 2);
			if (start < (ft_arrlen(data->line) - 1))
				ft_putstr_fd(" ", 2);
			start++;
		}
	}
	else if (n == 0 || (n == 1 && ft_arrlen(data->line) == 2))
		ft_putstr_fd("\n", 2);
}

// /*
// * execute builtin command echo (-n)
// */
// void	run_echo(t_data *data)
// {
// 	int	x;
// 	int	n;
// 	int	start;
// 	int	len;

// 	n = 0;
// 	len = ft_arrlen(data->line);
// 	if (len > 1)
// 	{
// 		x = 1;
// 		start = 1;
// 		printf("xxxxxxx\n");
// 		while (data->line[x])
// 		{
// 			if (is_nflag(data->line[x]) == TRUE)
// 			{
// 				n = 1;
// 				start++;
// 				x++;
// 			}
// 			else
// 				break ;
// 		}
// 		printf("n: %d\n", n);
// 		printf("start: %d\n", start);
// 		while (data->line[x])
// 		{
// 			if (x > start && x < len)
// 				ft_putstr_fd(" ", 2);
// 			ft_putstr_fd(data->line[x], 2);
// 			x++;
// 		}
// 	}
// 	if (n == 0 || (n == 1 && len == 2))
// 		ft_putstr_fd("\n", 2);
// }

/*
* execute builtin pwd
*/
void	run_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, 2);
    ft_putstr_fd("\n", 2);
}
