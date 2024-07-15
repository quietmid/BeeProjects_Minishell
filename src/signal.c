/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:52:41 by jlu               #+#    #+#             */
/*   Updated: 2024/07/15 18:02:11 by jlu              ###   ########.fr       */
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
	// printf("sdf\n");
	if (sig == SIGINT)
	{
		g_sigint = 1;
		close(STDIN_FILENO);
		write (1, "\n", 1);
	}
}
/*
* SIGINT - interrupt signal (ctrl + c)
* SIGQUIT - ctrl + \  does nothing
* EOF          ctrl + d
*/

int    set_signal_handler(int signum, void (*handler)(int))
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    if (sigaction(signum, &sa, NULL) < 0)
    {
        perror("minishell: sigaction");
        return (-1);
    }
    return (0);
}

void	toggle_input(int mode)
{
	struct termios term_m;

	tcgetattr(STDIN_FILENO, &term_m);
	if (mode == SIG_CHILD)
		term_m.c_lflag |= ECHOCTL;
	else
		term_m.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_m);
}


void	signal_setup(int mode)
{
	if (mode == SIG_PARENT)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_HEREDOC)
	{
		printf("SIG_heredoc\n");
		signal(SIGINT, heredoc_handler);
		// signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_CHILD)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
