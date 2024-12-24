/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:09:13 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 06:53:24 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*expand_dollar(char *str, int *i, t_envp *envp, int exit_status);
char	*join_char_to_str(char *result, char c);
void	remove_quotes(char *str);
void	free_and_shift(char **args, int index);

char	*expand_variable_in_str(char *str, t_data *data, int exit_status)
{
	char	*result;
	char	*tmp;
	int		i;
	int		in_single_quote;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_single_quote)
		{
			in_single_quote = 1;
			result = join_char_to_str(result, str[i++]);
			continue;
		}
		else if (str[i] == '\'' && in_single_quote)
		{
			in_single_quote = 0;
			result = join_char_to_str(result, str[i++]);
			continue;
		}
		if (str[i] == '$' && str[i + 1] && !in_single_quote)
		{
			tmp = expand_dollar(str, &i, data->e.envp, exit_status);
			if (!tmp)
				return (ft_free((void **)&result), NULL);
			result = ft_strjoin_free(result, tmp, 1);
			ft_free((void **)&tmp);
		}
		else
			result = join_char_to_str(result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

int	ft_expand_args(char **args, t_data *data, int exit_status)
{
	int		i;
	char	*expanded;

	if (!args || !*args)
		return (SUCCESS);
	i = 0;
	while (args[i])
	{
		expanded = expand_variable_in_str(args[i], data, exit_status);
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
