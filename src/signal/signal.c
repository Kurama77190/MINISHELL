/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/24 02:39:28 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_event_dummy(void)
{
	return (0);
}

void	restaure_SIGINT(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	ft_putstr_fd("\n", 2);
}

void	restaure_SIGQUIT(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_DFL);
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	heredoc_sigint_handler(__attribute__((unused)) int sig)
{
	g_exit_status = SIGINT;
	rl_done = 1;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_exit_status = SIGQUIT;
	
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(void)
{
	struct termios	terminal;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &terminal);
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	}
}
