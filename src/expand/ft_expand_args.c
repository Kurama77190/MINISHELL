/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:09:13 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 07:58:49 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char		*expand_dollar(char *str, int *i, t_envp *envp, int exit_status);
char		*join_char_to_str(char *result, char c);
void		remove_quotes(char *str);
void		free_and_shift(char **args, int index);

static bool	act1(char *str, int *i, int *single_quote, char **result)
{
	if (str[*i] == '\'' && !*single_quote)
	{
		*single_quote = 1;
		*result = join_char_to_str(*result, str[*i]);
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	act2(char *str, int *i, int *single_quote, char **result)
{
	if (str[*i] == '\'' && *single_quote)
	{
		*single_quote = 0;
		*result = join_char_to_str(*result, str[*i]);
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	act3(char *str, t_expand *expand, t_data *data, int exit_status)
{
	if (str[expand->i] == '"' && !expand->in_single_quote)
	{
		expand->result = join_char_to_str(expand->result, str[expand->i]);
		expand->i++;
		return (true);
	}
	if (str[expand->i] == '$' && str[expand->i + 1] && !expand->in_single_quote)
	{
		expand->tmp = expand_dollar(str, &expand->i, data->e.envp, exit_status);
		if (!expand->tmp)
		{
			ft_free((void **)&expand->result);
			return (false);
		}
		expand->result = ft_strjoin_free(expand->result, expand->tmp, 1);
		ft_free((void **)&expand->tmp);
		return (true);
	}
	return (false);
}

char	*expand_variable_in_str(char *str, t_data *data, int exit_status)
{
	t_expand	*e;

	e = &data->expand;
	e->result = ft_strdup("");
	if (!e->result)
		return (NULL);
	e->i = 0;
	e->in_single_quote = 0;
	while (str[e->i])
	{
		if (act1(str, &e->i, &e->in_single_quote, &e->result))
			continue ;
		else if (act2(str, &e->i, &e->in_single_quote, &e->result))
			continue ;
		else if (act3(str, e, data, exit_status))
			continue ;
		else
		{
			e->result = join_char_to_str(e->result, str[e->i]);
			e->i++;
		}
		if (!e->result)
			return (NULL);
	}
	return (e->result);
}

// char	*expand_variable_in_str(char *str, t_data *data, int exit_status)
// {
// 	char	*result;
// 	char	*tmp;
// 	int		i;
// 	int		in_single_quote;

// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	in_single_quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && !in_single_quote)
// 		{
// 			in_single_quote = 1;
// 			result = join_char_to_str(result, str[i++]);
// 			continue ;
// 		}
// 		else if (str[i] == '\'' && in_single_quote)
// 		{
// 			in_single_quote = 0;
// 			result = join_char_to_str(result, str[i++]);
// 			continue ;
// 		}
// 		if (str[i] == '$' && str[i + 1] && !in_single_quote)
// 		{
// 			tmp = expand_dollar(str, &i, data->e.envp, exit_status);
// 			if (!tmp)
// 				return (ft_free((void **)&result), NULL);
// 			result = ft_strjoin_free(result, tmp, 1);
// 			ft_free((void **)&tmp);
// 		}
// 		else
// 			result = join_char_to_str(result, str[i++]);
// 		if (!result)
// 			return (NULL);
// 	}
// 	return (result);
// }

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
