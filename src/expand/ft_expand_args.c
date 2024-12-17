/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:09:13 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 09:09:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"
#include "minishell.h"

static char	*expand_variable_in_str(char *str, t_envp *envp);
static void	remove_quotes(char *str);
static void	free_and_shift(char **args, int index);

int	ft_expand_args(char **args, t_envp *envp)
{
	int		i;
	char	*expanded;

	if (!args || !*args)
		return (SUCCESS);
	i = 0;
	while (args[i])
	{
		expanded = expand_variable_in_str(args[i], envp);
		if (!expanded)
			return (ERROR); // Erreur d'allocation mémoire
		free(args[i]); // Libère l'ancienne valeur
		args[i] = expanded;
		remove_quotes(args[i]);
		if (!args[i][0]) // Argument vide après expansion
		{
			free_and_shift(args, i);
			continue; // Passe directement à l'index actuel (déjà shifté)
		}
		i++;
	}
	return (SUCCESS);
}

static char	*expand_variable_in_str(char *str, t_envp *envp)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			int start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			tmp = ft_substr(str, start, i - start);
			if (!tmp)
				return (free(result), NULL);
			result = ft_strjoin_free(result, get_env_value(tmp, envp), 1);
			free(tmp);
		}
		else
			result = ft_strjoin_free(result, ft_substr(str, i++, 1), 1);
	}
	return (result);
}

static void	free_and_shift(char **args, int index)
{
	free(args[index]);
	while (args[index])
	{
		args[index] = args[index + 1];
		index++;
	}
}

static void	remove_quotes(char *str)
{
	int		i;
	int		j;
	char	in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!in_quote || in_quote == str[i]))
			in_quote = in_quote ? 0 : str[i];
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}
