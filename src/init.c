/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:52:41 by jlu               #+#    #+#             */
/*   Updated: 2024/05/30 17:33:05 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* this file should look to initialize minishell with the signal
*/

/*
* this handles the signals like ctrl - c | ctrl \ | ctrl d
*/

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
		readline("\nminishell-8.8$ ");
	else if (sig == SIGKILL)
	{
		printf("exit");
		exit(EXIT_SUCCESS) ;
	}
}
/*
* SIGINT - interrupt signal (ctrl + c)
* SIGKILL - Kill signal 
* SIGQUIT - ctrl + \  does nothing
*           ctrl + d
*/

void	signal_setup(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}