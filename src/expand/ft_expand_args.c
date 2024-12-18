/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:09:13 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/18 02:25:46 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"
#include "minishell.h"

static char	*expand_variable_in_str(char *str, t_envp *envp, int exit_status);

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
			return (ERROR); // Erreur d'allocation mémoire
		ft_free((void**)&args[i]); // Libère l'ancienne valeur
		args[i] = expanded;
		remove_quotes(args[i]);
		if (!args[i][0]) // Si argument vide après expansion
		{
			free_and_shift(args, i);
			continue; // Passe directement à l'index actuel (déjà shifté)
		}
		i++;
	}
	return (SUCCESS);
}

static char	*expand_variable_in_str(char *str, t_envp *envp, int exit_status)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (handle_dollar_case(&result, str, &i, envp, exit_status) == ERROR)
				return (ft_free((void **)&result), NULL);
		}
		else
		{
			if (append_char_to_result(&result, str[i++]) == ERROR)
				return (NULL);
		}
	}
	return (result);
}

static int	handle_dollar_case(char **result, char *str, int *i,
								t_envp *envp, int exit_status)
{
	char	*expanded_value;

	if (str[*i + 1] == '?')
		expanded_value = handle_exit_status(i, exit_status);
	else
		expanded_value = extract_env_var(str, i, envp);
	if (!expanded_value)
		return (ERROR);
	if (append_value_to_result(result, expanded_value) == ERROR)
		return (ft_free((void **)&expanded_value), ERROR);
	ft_free((void **)&expanded_value);
	return (SUCCESS);
}

static char	*handle_exit_status(int *i, int exit_status)
{
	char	*status_str;

	(*i) += 2; // Skip $?
	status_str = ft_itoa(exit_status);
	return (status_str);
}

static char	*extract_env_var(char *str, int *i, t_envp *envp)
{
	char	*key;
	char	*value;
	int		start;
	int		len;

	start = ++(*i);
	len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		len++;
		(*i)++;
	}
	key = ft_substr(str, start, len);
	if (!key)
		return (NULL);
	value = get_env_value(key, envp);
	ft_free((void **)&key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	handle_dollar_case(char **result, char *str, int *i, t_envp *envp)
{
	char	*expanded_value;

	if (str[*i + 1] == '?')
		expanded_value = handle_exit_status(i);
	else
		expanded_value = extract_env_var(str, i, envp);
	if (!expanded_value)
		return (ERROR);
	if (append_value_to_result(result, expanded_value) == ERROR)
		return (ft_free((void **)&expanded_value), ERROR);
	ft_free((void **)&expanded_value);
	return (SUCCESS);
}

static char	*handle_exit_status(int *i)
{
	extern int	g_exit_status;
	char		*status_str;

	(*i) += 2; // Skip $?
	status_str = ft_itoa(g_exit_status);
	return (status_str);
}

static int	append_value_to_result(char **result, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(*result, value);
	if (!tmp)
		return (ERROR);
	ft_free((void **)result);
	*result = tmp;
	return (SUCCESS);
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
