/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:56:36 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 11:37:52 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*new_export_envp(char *str);

int	lstadd_envp(t_data *data, char *str)
{
	t_envp	*new;
	t_envp	*tmp;

	new = new_export_envp(str);
	if (!new)
		return (ERROR);
	tmp = data->e.envp;
	if (!tmp)
	{
        tmp = new;
	}
	else
	{
		while (tmp)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
        new->next = NULL;
	}
    return (SUCCESS);
}

static t_envp	*new_export_envp(char *str)
{
	t_envp *new;

	new = ft_calloc(0, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->line = ft_strdup(str);
	if (!new->line)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
    return (new);
}

bool	ft_is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (true);
	return (false);
}