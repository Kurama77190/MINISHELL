/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/21 11:55:06 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// // Handler for heredoc interruptions
// void heredoc_sigint_handler(int sig)
// {
//     (void)sig;
//     g_exit_status = 130; // Exit status for SIGINT
//     ft_putstr_fd("\n", STDOUT_FILENO);
//     close(STDIN_FILENO); // Close stdin to terminate heredoc
// }

// // Handler for SIGQUIT
// void sigquit_handler(int sig)
// {
//     (void)sig;
//     g_exit_status = 131; // Exit status for SIGQUIT
//     ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
// }

// // Handler for SIGINT in shell prompt
// void sigint_handler(int sig)
// {
//     (void)sig;
//     g_exit_status = 130; // Exit status for SIGINT
//     ft_putstr_fd("ˆC\n", STDOUT_FILENO);
//     rl_replace_line("", 1); // Clear current input line
//     rl_on_new_line();       // Move to new line
//     rl_redisplay();         // Redisplay the prompt
// }

// Configure signals for the shell
// void signals(void)
// {
//     struct termios terminal;

//     // Configure terminal to ignore ECHOCTL (disable ^C display)
//     tcgetattr(STDIN_FILENO, &terminal);
//     terminal.c_lflag &= ~(ECHO | ICANON);
//     tcsetattr(STDIN_FILENO, TCSANOW, &terminal);

//     // Signal handlers
//     signal(SIGINT, sigint_handler); // Handle Ctrl+C
//     signal(SIGQUIT, SIG_IGN);       // Ignore Ctrl+
//     signal(SIGTERM, SIG_IGN);       // Ignore termination signals
//     signal(SIGTSTP, SIG_IGN);       // Ignore Ctrl+Z
// }



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
void	signals(void)
{
	struct termios terminal;
	
	// terminal.c_lflag &= ~ECHOCTL;
	tcgetattr(STDIN_FILENO, &terminal);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}
