/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 02:34:12 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/18 02:43:12 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(char *str, int *i, t_envp *envp, int exit_status)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_status));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	value = get_env_value(var_name, envp);
	ft_free((void **)&var_name);
	return (value ? ft_strdup(value) : ft_strdup(""));
}

char	*join_char_to_str(char *result, char c)
{
	char	*tmp;
	char	buffer[2];

	buffer[0] = c;
	buffer[1] = '\0';
	tmp = ft_strjoin(result, buffer);
	ft_free((void **)&result);
	return (tmp);
}

void	remove_quotes(char *str)
{
	int		i;
	int		j;
	char	in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!in_quote
				|| in_quote == str[i]))
			in_quote = in_quote ? 0 : str[i];
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	free_and_shift(char **args, int index)
{
	free(args[index]);
	while (args[index])
	{
		args[index] = args[index + 1];
		index++;
	}
}
