/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:21:56 by samy              #+#    #+#             */
/*   Updated: 2024/10/29 19:33:56 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_redir(t_token **new, char *token)
{
    int len;

    len = ft_strlen(token);
    if (ft_strnstr(token, ">>", len) != NULL)
    {
        (*new)->redir_type |= APPEND_OUT;
        (*new)->file_out = ft_strtrim(token + 2, " ");
    }
    else if (ft_strnstr(token, "<<", len) != NULL)
    {
        (*new)->redir_type |= HERE_DOC;
        (*new)->file_in = ft_strtrim(token + 2, " ");
    }
    else if (ft_strnstr(token, "<", len) != NULL)
    {
        (*new)->redir_type |= REDIR_IN;
        (*new)->file_in = ft_strtrim(token + 1, " ");
    }
    else if (ft_strnstr(token, ">", len) != NULL)
    {
        (*new)->redir_type |= REDIR_OUT;
        (*new)->file_out = ft_strtrim(token + 1, " ");
    }
}

// void set_commands_args(t_token **new, char **splited)
// {
// 	int i;

// 	i = 0;
// 	while (splited[i])
// 	{
// 		if (i == 0)
// 			(*new)->command = ft_strdup(splited[i]);
// 		else
// 			ft_lstadd_back(&(*new)->args, ft_lstnew(ft_strdup(splited[i])));
// 		i++;
// 	}
// }

