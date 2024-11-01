/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ralph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:54:38 by samy              #+#    #+#             */
/*   Updated: 2024/11/01 17:04:29 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // tu peux mettre tes structures dedans ou recreer un header exec.h has u want



/*
	exemple d execution avec la liste chainer :

typedef struct s_token
{
    char            *command;    // Nom de la commande
    char            **args;      // Tableau des arguments
	char			*here_stop;	 // Nom stop here_doc
    int             fd_in;       // Descripteur pour redirection d'entrée
    int             fd_out;      // Descripteur pour redirection de sortie
    char            *file_in;    // Nom du fichier d'entrée (si redirection)
    char            *file_out;   // Nom du fichier de sortie (si redirection)
    t_type          types;        // Type de la commande (COMMAND, PIPE, etc.)
    t_type          redir_type;  // Type de redirection (REDIR, HERE_DOC, etc.)
    int             builtin;     // 1 si c'est un builtin, 0 si binaire externe
    int             fd_pipe[2];  // Pipe utilisé pour relier la sortie et l'entrée entre commandes
    struct s_token  *next;       // Pointeur vers le prochain nœud
    struct s_token  *prev;       // Pointeur vers le nœud précédent
} 					t_token;

*/

int exec_command(t_data *data)
{
    t_token *current;

    current = data->token_manag.token;

    while (current)
    {
        if (current->types & COMMAND)
        {
            if ((current->types & PIPE) == 0)
            {
                if (current->builtin == 0)
                {
                    // Vérifie s'il y a une redirection ou non
                    // Exécuter une commande simple non builtin sans pipe
                }
                else if (current->builtin == 1)
                {
                    // Vérifie s'il y a une redirection ou non
                    // Exécuter un builtin sans pipe
                }
            }
            else if (current->types & PIPE)
            {
                if (current->builtin == 0)
                {
                    // Vérifie s'il y a une redirection ou non
                    // Exécuter une commande simple non builtin avec pipe
                }
                else if (current->builtin == 1)
                {
                    // Vérifie s'il y a une redirection ou non
                    // Exécuter un builtin avec pipe
                }
            }
        }
        current = current->next;
    }
    return (SUCCESS);
}
