/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:24:39 by samy              #+#    #+#             */
/*   Updated: 2024/12/13 23:11:55 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	ft_is_operator(char c)
// {
// 	return (c == '<' || c == '>' || c == '&' || c == '|' || c == ';' || c == '&' ||
// 	c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '*' || c == '('
// 	|| c == ')' || c == '+' || c == '-');
// }

// char	*infile_name(char *token);
// char	*infile_type(char *token);

// t_redir	*new_redir_in(t_redir_manag	*param, char *token)
// {
// 	t_redir	*new;
// 	char	*tmp;

// 	new = ft_calloc(1, sizeof(t_redir));
// 	if (!new)
// 		return (NULL);
	
// 	new->file_name = infile_name(token);
// 	if (!new->file_name)
// 		return (NULL);
// 	new->type = infile_type(token);
// 	if (!new->file_name)
// 		return (NULL);
// }

// t_redir	*new_redir_out(t_redir_manag	*param, char *token)
// {
// 	t_redir	*new;
// 	char	*tmp;

// 	new = ft_calloc(1, sizeof(t_redir));
// 	if (!new)
// 		return (NULL);
	
// 	new->file_name = outfile_name(token);
// 	if (!new->file_name)
// 		return (NULL);
// 	new->type = outfile_type(token);
// 	if (!new->file_name)
// 		return (NULL);
// }

// char	*outfile_type(char *token)
// {
// 	char	*tmp;
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	tmp = ft_strchr(token, '>');
// 	if (!tmp)
// 		return (token);
// 	while (tmp[i] && tmp[i] != ' ')
// 		i++;
// 	result = ft_substr(tmp, 0, i);
// 	if (!result)
// 		return (NULL);
// 	while (*tmp && i > 0)
// 	{
// 		*tmp = ' ';
// 		tmp++;
// 		i--;
// 	}
// 	return (result);
// }

// char	*infile_type(char *token)
// {
// 	char	*tmp;
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	tmp = ft_strchr(token, '<');
// 	if (!tmp)
// 		return (token);
// 	while (tmp[i] && tmp[i] != ' ')
// 		i++;
// 	result = ft_substr(tmp, 0, i);
// 	if (!result)
// 		return (NULL);
// 	while (*tmp && i > 0)
// 	{
// 		*tmp = ' ';
// 		tmp++;
// 		i--;
// 	}
// 	return (result);
// }

// char	*outfile_name(char *token)
// {
// 	char	*tmp;
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	tmp = ft_strchr(token, '>');
// 	if (!tmp)
// 		return (token);
// 	while (ft_is_operator(*tmp))
// 		tmp++;
// 	if (*tmp == '\0')
// 		return (token);
// 	while (tmp[i] && !ft_is_operator(tmp[i]))
// 		i++;
// 	result = ft_substr(tmp, 0, i);
// 	if (!result)
// 		return (NULL);
// 	while (*tmp && i > 0)
// 	{
// 		*tmp = ' ';
// 		tmp++;
// 		i--;
// 	}
// 	return (result);
// }

// char	*infile_name(char *token)
// {
// 	char	*tmp;
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	tmp = ft_strchr(token, '<');
// 	if (!tmp)
// 		return (token);
// 	while (ft_is_operator(*tmp))
// 		tmp++;
// 	if (*tmp == '\0')
// 		return (token);
// 	while (tmp[i] && !ft_is_operator(tmp[i]))
// 		i++;
// 	result = ft_substr(tmp, 0, i);
// 	if (!result)
// 		return (NULL);
// 	while (*tmp && i > 0)
// 	{
// 		*tmp = ' ';
// 		tmp++;
// 		i--;
// 	}
// 	return (result);
// }

// int	add_redir_in(t_data *data, char *token, t_redir_manag *param)
// {
// 	t_redir	*new;
// 	t_redir	*tmp;

// 	new = new_redir_in(param, token);
// 	if (!new)
// 		return (ERROR);
// 	if (param->head == NULL)
// 	{
// 		param->head = new;
// 		new->next = NULL;
// 		new->prev = NULL;
// 	}
// 	else
// 	{
// 		tmp = param->current;
// 		while (tmp->next != NULL)
// 			tmp->next;
// 		tmp->next = new;z
// 		new->prev = tmp;
// 		new->next = NULL;
// 	}
// 	return (SUCCESS);
// }



int main(void)
{
	// t_data data;
	// while (1)
	// {
	
	// 	char *token = readline("MINISHELL TEST ");
	// 	if (!token)
	// 		exit(0);
	// printf("result name infile : %s\n", infile_name(token));
	// printf("resultat type infile : %s\n", infile_type(token));
	// printf("le reste du prompt : %s\n", token);
		
	// }
	printf ("\033[12;01mBonjour\033[00m\n");
	printf("\033[30mTexte noir\033[0m\n");
	printf("\033[31mTexte rouge\033[0m\n");
	printf("\033[32mTexte vert\033[0m\n");
	printf("\033[33mTexte jaune\033[0m\n");
	printf("\033[34mTexte bleu\033[0m\n");
	printf("\033[35mTexte magenta\033[0m\n");
	printf("\033[36mTexte cyan\033[0m\n");
	printf("\033[37mTexte blanc\033[0m\n");
	printf("\033[90mTexte noir vif\033[0m\n");
	printf("\033[91mTexte rouge vif\033[0m\n");
	printf("\033[92mTexte vert vif\033[0m\n");
	printf("\033[93mTexte jaune vif\033[0m\n");
	printf("\033[94mTexte bleu vif\033[0m\n");
	printf("\033[95mTexte magenta vif\033[0m\n");
	printf("\033[96mTexte cyan vif\033[0m\n");
	printf("\033[97mTexte blanc vif\033[0m\n");
	printf("\033[1mTexte en gras\033[0m\n");
	printf("\033[3mTexte en italique\033[0m\n");
	printf("\033[4mTexte souligné\033[0m\n");
	printf("\033[7mTexte inversé (fond et texte échangés)\033[0m\n");
	printf("\033[9mTexte barré\033[0m\n");
    printf("\033[1;31mTexte rouge en gras\033[0m\n");
    printf("\033[4;34mTexte bleu souligné\033[0m\n");
    printf("\033[3;32;47mTexte vert en italique sur fond blanc\033[0m\n");
    printf("\033[7;35mTexte magenta inversé\033[0m\n");
    printf("\033[0mTexte normal\n");
	return (0);
}
// Compare this snippet from src/parsing/handle_redir.c: