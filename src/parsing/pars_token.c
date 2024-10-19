/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:00:51 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:13 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		identifier_token(t_data *data, char *token);

int	pars_token(t_data *data)
{
	int	i;

	data->token_manag.readed = ft_split(data->prompt.read_line, '|');
	if (!data->token_manag.readed)
		return (ERROR);
	i = 0;
	while (data->token_manag.readed[i])
	{
		if (identifier_token(data, data->token_manag.readed[i]) == ERROR)
			return (free_split(data->token_manag.readed), ERROR);
		i++;
	}
	free_split(data->token_manag.readed);
	return (SUCCESS);
}

// typedef enum e_type
// {
//     TYPE_NONE   = 0,
//     COMMAND     = 1 << 0,   // 0001
//     PIPE        = 1 << 1,   // 0010
//     REDIR_IN    = 1 << 2,   // 0100
//     REDIR_OUT   = 1 << 3,   // 1000
// }   t_type;

// typedef struct s_token
// {
//     char            *command;    // Nom de la commande
//     char            **args;      // Tableau des arguments
//     char				*here_stop;
//     int             fd_in;       // Descripteur pour redirection d'entrée
//     int             fd_out;      // Descripteur pour redirection de sortie
//     char            *file_in;    // Nom du fichier d'entrée (si redirection)
//     char            *file_out;   // Nom du fichier de sortie (si redirection)
//     t_type          types;        // Type de la commande (COMMAND, PIPE,
	// etc.)
// t_type          redir_type;  // Type de redirection (REDIR, HERE_DOC, etc.)
//     int             builtin;     // 1 si c'est un builtin,
//     int             fd_pipe[2]; 
	// Pipe utilisé pour relier la sortie et l'entrée entre commandes
//     struct s_token  *next;       // Pointeur vers le prochain nœud
//     struct s_token  *prev;       // Pointeur vers le nœud précédent
// } 					t_token;

// cmd : /dev/stdin < cat| ls > /dev/stdout
int	identifier_token(t_data *data, char *token)
{
	char	**splited;
	int		i;

	(void)data;
	splited = split_token(token);
	i = 0;
	while (splited[i])
	{
		printf("[tab%i] = %s", i, splited[i]);
		i++;
	}
	printf("\n");
	free_split(splited);
	return (SUCCESS);
	// printf("%s\n");
	// if (is_builtin)
	// if (is_pipe)
	// if (is redir)
	// if (is_here_doc)
	// if (is)
	// else
	// is_command();
}

// int	add_in_list_token(t_data *data)
// {
// 	//
// }

void	set_redir(t_token **new, char *token);

t_token	*new_lst_token(t_data *data, char *token, char **token_splited)
{
	t_token	*new;
	int		i;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	set_redir(&new, token);// helpers
	set_commands_args(&new, token_splited);// helpers
	return (new);
}

void set_redir(t_token **new, char *token)
{
    int len;
    char *filename;

    len = ft_strlen(token);
    if (ft_strnstr(token, "<", len) != NULL)
    {
        (*new)->redir_type |= REDIR_IN;
        filename = ft_strtrim(token + 1, " ");
    }
    else if (ft_strnstr(token, ">", len) != NULL)
    {
        (*new)->redir_type |= REDIR_OUT;
        filename = ft_strtrim(token + 1, " ");
    }
    else if (ft_strnstr(token, ">>", len) != NULL)
    {
        (*new)->redir_type |= APPEND_OUT;
        filename = ft_strtrim(token + 2, " ");
    }
    else if (ft_strnstr(token, "<<", len) != NULL)
    {
        (*new)->redir_type |= HERE_DOC;
        filename = ft_strtrim(token + 2, " ");
    }
    else
        return;
    if (filename)
        (*new)-> = filename;
}

 
void	set_commands_arg(t_token **new, char **splited)
{
}



// ordre d execution absolu, peut importe l ordre et les commands donner a UNIX, celui ci l interpretre dans un ordre bien specifique,
// regarder les redir in and out et les set
// par la suite il regarde la commande et c arguments
// apres cela il pourra commencer le input, la commandes avec c arguments et son output !
// grace a ca nous pourrons peut importe ou se trouve la redirection sur la commande avoir exactement le meme comportement que minishell.
// ENJOY SBEN TAY! =D