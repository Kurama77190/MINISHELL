/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/24 04:01:28 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_event_dummy(void)
{
	return (0);
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
