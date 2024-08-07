/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:52:41 by jlu               #+#    #+#             */
/*   Updated: 2024/07/24 22:02:50 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* SIGINT - interrupt signal (ctrl + c)
* SIGQUIT - ctrl + \  does nothing
* EOF          ctrl + d
*/

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sigint = 130;
	}
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = 1;
		close(STDIN_FILENO);
		write (1, "\n", 1);
	}
}

int	set_signal_handler(int signum, void (*handler)(int), t_data *data)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
	{
		perror("minishell: sigaction");
		return (-1);
	}
	if (g_sigint == 1)
	{
		data->status = 130;
		g_sigint = 0;
	}
	return (0);
}

void	toggle_input(int mode)
{
	struct termios	term_m;

	tcgetattr(STDIN_FILENO, &term_m);
	if (mode == SIG_CHILD)
		term_m.c_lflag |= ECHOCTL;
	else
		term_m.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_m);
}

void	signal_setup(int mode, t_data *data)
{
	if (mode == SIG_PARENT)
	{
		set_signal_handler(SIGINT, sig_handler, data);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_HEREDOC)
	{
		set_signal_handler(SIGINT, heredoc_handler, data);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_CHILD)
	{
		set_signal_handler(SIGINT, sig_handler, data);
		signal(SIGQUIT, SIG_IGN);
	}
}
