/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:11:23 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 11:04:14 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

void	set_terminal_flag(int flag)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag = flag;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
	}
}

void	ft_sig_handling(int sig)
{
	if (sig == SIGINT)
	{
		set_terminal_flag(ISIG);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_terminal_flag(ISIG | ECHO | ICANON);
	}
}

void	ft_sig_heredoc(int sig)
{
	write(1, "\n", 1);
	close(0);
	(void) sig;
}

void	ft_handler_signal(int pick)
{
	struct sigaction	sa_sig;

	signal(SIGTSTP, SIG_IGN);
	if (pick == 1)
	{
		sa_sig.sa_handler = &ft_sig_heredoc;
		sigaction(SIGINT, &sa_sig, NULL);
	}
	else if (pick == 2)
		signal(SIGINT, SIG_IGN);
	else if (pick == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		sa_sig.sa_flags = SA_RESTART;
		sa_sig.sa_handler = &ft_sig_handling;
		sigaction(SIGINT, &sa_sig, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
