/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:11:23 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/19 22:25:54 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

void ft_sig_handling(int sig)
{
    struct termios term;

    if (sig == SIGINT)
    {
        // Disable ISIG to suppress ^C
        if (tcgetattr(STDIN_FILENO, &term) == -1)
        {
            perror("tcgetattr");
            return;
        }
        term.c_lflag &= ~ISIG; // Disable ISIG
        if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
        {
            perror("tcsetattr");
            return;
        }

        // Print a newline
        write(STDOUT_FILENO, "\n", 1);

        // Display the prompt
        rl_on_new_line(); // Tell readline to move to a new line
        rl_replace_line("", 0); // Clear the current input line
        rl_redisplay(); // Redisplay the prompt

        // Restore ISIG after handling the signal
        term.c_lflag |= ISIG; // Re-enable ISIG
        if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
        {
            perror("tcsetattr");
            return;
        }
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
