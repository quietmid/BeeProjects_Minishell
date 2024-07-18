/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:22:11 by pbumidan          #+#    #+#             */
/*   Updated: 2024/07/18 15:24:49 by pbumidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_digit(t_data *data, char *str)
{
    int x;
    
    (void)data;
    x = 0;
    while(str[x])
    {
        if (ft_isdigit(str[x]) == 1)
            return(FALSE);
        x++;
    }
    return (TRUE);
}

void    exit_message(t_data *data, char *var, int c)
{
    (void)data;
    ft_putstr_fd("exit\n", 2);
    ft_putstr_fd("minishell-8.8$: ", 2);
    if (c == 1)
        ft_putstr_fd("exit: too many arguments\n", 2);
    if (c == 2)
    {
        ft_putstr_fd(var, 2);
        ft_putendl_fd(": numeric argument required", 2);
    }
}

void    run_exit(t_data *data)
{
    if (ft_arr_len(data->token[0].cmd) > 2)
    {
        if (is_digit(data, data->token[0].cmd[1]) == TRUE)
        {
            exit_message(data, data->token[0].cmd[1], 2);
            data->status = 2;
            free_data_all(data, 0);
            exit(data->status);
        }
        exit_message(data, NULL, 1);
        data->status = 1;
        return ;
    }
    else
    {
        free_data_all(data, 0);
        exit(data->status);
    }
}