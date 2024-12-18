/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:01:07 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/18 02:11:25 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_valid_pipes(const char *str);
static int	find_next_pipe(const char *str, int start);
static char	*allocate_section(const char *str, int start, int end);

char	**split_pipes_secure(const char *str)
{
	char	**result;
	int		pipe_count;
	int		start;
	int		end;
	int		i;

	pipe_count = count_valid_pipes(str);
	result = malloc(sizeof(char *) * (pipe_count + 1));
	if (!result)
		return (NULL);
	start = 0;
	i = 0;
	end = find_next_pipe(str, start);
	while (end != -1)
	{
		result[i] = allocate_section(str, start, end);
		if (!result[i++])
			return (free_split(result), NULL);
		start = end + 1;
		end = find_next_pipe(str, start);
	}
	result[i] = allocate_section(str, start, ft_strlen(str));
	if (!result[i])
		return (free_split(result), NULL);
	return (result[++i] = NULL, result);
}

static int	count_valid_pipes(const char *str)
{
	int		i;
	int		count;
	char	in_quote;

	i = 0;
	count = 1;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == 0)
				in_quote = str[i];
			else if (in_quote == str[i])
				in_quote = 0;
		}
		if (str[i] == '|' && in_quote == 0)
			count++;
		i++;
	}
	return (count);
}

static int	find_next_pipe(const char *str, int start)
{
	int		i;
	char	in_quote;

	i = start;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == 0)
				in_quote = str[i];
			else if (in_quote == str[i])
				in_quote = 0;
		}
		if (str[i] == '|' && in_quote == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*allocate_section(const char *str, int start, int end)
{
	char	*section;
	int		len;

	len = end - start;
	section = ft_calloc(len + 1, sizeof(char));
	if (!section)
		return (NULL);
	ft_strlcpy(section, str + start, len + 1);
	return (section);
}
