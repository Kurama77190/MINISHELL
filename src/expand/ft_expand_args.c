/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:09:13 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 02:46:23 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*expand_dollar(char *str, int *i, t_envp *envp, int exit_status);
char	*join_char_to_str(char *result, char c);
void	remove_quotes(char *str);
void	free_and_shift(char **args, int index);

int	ft_expand_args(char **args, t_envp *envp, int exit_status)
{
	int		i;
	char	*expanded;

	if (!args || !*args)
		return (SUCCESS);
	i = 0;
	while (args[i])
	{
		expanded = expand_variable_in_str(args[i], envp, exit_status);
		if (!expanded)
			return (ERROR);
		ft_free((void **)&args[i]);
		args[i] = expanded;
		remove_quotes(args[i]);
		if (!args[i][0])
		{
			free_and_shift(args, i);
			continue ;
		}
		i++;
	}
	return (SUCCESS);
}
