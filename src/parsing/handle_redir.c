/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:42:18 by samy              #+#    #+#             */
/*   Updated: 2024/12/13 03:53:53 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*infile_name(char *token);
char	*infile_type(char *token);
bool	ft_is_operator(char c);
t_redir	*new_redir_in(t_redir_manag *param, char *token);
t_redir	*new_redir_out(t_redir_manag *param, char *token);
char	*outfile_type(char *token);
char	*infile_type(char *token);
int		add_redir_in(t_data *data, char *token, t_redir_manag *param);
int		add_redir_out(t_data *data, char *token, t_redir_manag *param);

int	setup_redir(t_data *data, char *token, t_token *new)
{
	t_redir_manag	*redir_in;
	t_redir_manag	*redir_out;

	new->redir_in = ft_calloc(1, sizeof(t_redir_manag));
	if (!new->redir_in)
		return (ERROR);
	new->redir_out = ft_calloc(1, sizeof(t_redir_manag));
	if (!new->redir_out)
	{
		ft_free((void **)&new->redir_in);
		return (ERROR);
	}
	redir_in = new->redir_in;
	redir_out = new->redir_out;
	if (add_redir_in(data, token, redir_in) == ERROR)
		return (ERROR);
	if (add_redir_out(data, token, redir_out))
		return (ERROR);
	return (SUCCESS);
}

t_redir	*new_redir_in(t_redir_manag *param, char *token)
{
	t_redir	*new;

	(void)param;
	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = infile_name(token);
	if (!new->file_name)
		return (NULL);
	new->type = infile_type(token);
	if (!new->file_name)
		return (NULL);
	return (new);
}

t_redir	*new_redir_out(t_redir_manag *param, char *token)
{
	t_redir	*new;

	(void)param;
	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = outfile_name(token);
	if (!new->file_name)
		return (NULL);
	new->type = outfile_type(token);
	if (!new->file_name)
		return (NULL);
	return (new);
}

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
	while (*tmp && i > 0)
	{
		*tmp = ' ';
		tmp++;
		i--;
	}
	return (result);
}

char	*infile_type(char *token)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '<');
	if (!tmp)
		return ("NONE\0");
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '>')
		i++;
	result = ft_substr(tmp, 0, i);
	if (!result)
		return (NULL);
	while (*tmp && i > 0)
	{
		*tmp = ' ';
		tmp++;
		i--;
	}
	return (result);
}

char	*outfile_name(char *token)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '>');
	if (!tmp)
		return ("NONE\0");
	while (*tmp == '>')
		tmp++;
	if (*tmp == '\0'  || *tmp == '<')
		return ("NONE\0");
	while (tmp[i] && !ft_is_operator(tmp[i]))
		i++;
	result = ft_substr(tmp, 0, i);
	if (!result)
		return (NULL);
	while (*tmp && i > 0)
	{
		*tmp = ' ';
		tmp++;
		i--;
	}
	return (result);
}

	char	*infile_name(char *token)
	{
		char	*tmp;
		char	*result;
		int		i;

		i = 0;
		tmp = ft_strchr(token, '<');
		if (!tmp)
			return ("NONE\0");
		while (*tmp == '<')
			tmp++;
		if (*tmp == '\0' || *tmp == '>')
			return ("NONE\0");
		while (tmp[i] && !ft_is_operator(tmp[i]))
			i++;
		result = ft_substr(tmp, 0, i);
		if (!result)
			return (NULL);
		while (*tmp && i > 0)
		{
			*tmp = ' ';
			tmp++;
			i--;
		}
		return (result);
	}

int	add_redir_in(t_data *data, char *token, t_redir_manag *param)
{
	t_redir	*new;
	t_redir	*tmp;

	(void)data;
	new = new_redir_in(param, token);
	if (!new)
		return (ERROR);
	if (param->head == NULL)
	{
		param->head = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = param->current;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (SUCCESS);
}

int	add_redir_out(t_data *data, char *token, t_redir_manag *param)
{
	t_redir	*new;
	t_redir	*tmp;

	(void)data;
	new = new_redir_out(param, token);
	if (!new)
		return (ERROR);
	if (param->head == NULL)
	{
		param->head = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = param->current;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (SUCCESS);
}
