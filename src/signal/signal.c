/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/30 16:26:13 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	close(STDIN_FILENO);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_exit_status = 131;
	ft_putstr_fd("Quit: 3\n", 1);
}

// Launch CONTROL C
void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(t_data *data)
{
	struct termios	terminal;

	terminal = data->terminal;
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
