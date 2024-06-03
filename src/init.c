/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:52:41 by jlu               #+#    #+#             */
/*   Updated: 2024/06/03 13:54:09 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* this file should look to initialize minishell with the signal
*/

/*
* this handles the signals like ctrl - c | ctrl \ | ctrl d
*/

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write (1, "\n", 1);
		rl_redisplay();
	}
}
/*
* SIGINT - interrupt signal (ctrl + c)
* SIGQUIT - ctrl + \  does nothing
* EOF          ctrl + d
*/

void	signal_setup(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}