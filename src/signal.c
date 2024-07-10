/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:52:41 by jlu               #+#    #+#             */
/*   Updated: 2024/07/10 16:13:32 by jlu              ###   ########.fr       */
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
		write (1, "\n", 1);
		rl_on_new_line(); // inform readline that the cursor is on a newline
		rl_replace_line("", 0); // clear the current line buffer
		rl_redisplay(); // Redisplay the prompt and input line;
	}
}
void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		//close (); we need to close whatever we have been writing into
	}
}
/*
* SIGINT - interrupt signal (ctrl + c)
* SIGQUIT - ctrl + \  does nothing
* EOF          ctrl + d
*/

void	signal_setup(int mode)
{
	struct termios term_m;

	tcgetattr(STDIN_FILENO, &term_m);
	if (mode == SIG_CHILD)
		term_m.c_lflag |= ECHOCTL;
	else
		term_m.c_lflag &= ~ECHOCTL;
	tcsetattr(STDERR_FILENO, TCSANOW, &term_m);
	if (mode == SIG_PARENT)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_HEREDOC)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_CHILD)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
