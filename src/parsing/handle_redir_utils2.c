/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:13:26 by samy              #+#    #+#             */
/*   Updated: 2024/12/13 15:21:48 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*outfile_type(char *token)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '>');
	if (!tmp)
		return ("NONE\0");
	while (tmp[i] && tmp[i] != ' ')
		i++;
	result = ft_substr(tmp, 0, i);
	if (!result)
		return (NULL);
	delete_word(tmp, i, 0);
	return (result);
}

char	*infile_type(char *token)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '<');
	if (!tmp || is_operator_in_quotes(token, '<'))
		return ("NONE\0");
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '>')
		i++;
	result = ft_substr(tmp, 0, i);
	if (!result)
		return (NULL);
	delete_word(tmp, i, 0);
	return (result);
}

char	*outfile_name(char *token)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '>');
	if (!tmp || is_operator_in_quotes(token, '>'))
		return ("NONE");
	while (*tmp == '>' || ft_isspace(*tmp))
		tmp++;
	if (*tmp == '\0' || ft_is_operator(*tmp))
		return ("NONE");
	found_index(tmp, &i);
	result = ft_substr(tmp, 0, i);
	if (!result)
		return (NULL);
	delete_word(tmp, i, 0);
	return (result);
}

char	*infile_name(char *token)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '<');
	if (!tmp || is_operator_in_quotes(token, '<'))
		return ("NONE");
	while (*tmp == '<' || ft_isspace(*tmp))
		tmp++;
	if (*tmp == '\0' || ft_is_operator(*tmp))
		return ("NONE");
	found_index(tmp, &i);
	result = ft_substr(tmp, 0, i);
	if (!result)
		return (NULL);
	delete_word(tmp, i, 0);
	return (result);
}
