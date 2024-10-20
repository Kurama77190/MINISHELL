#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

# define ERROR 1
# define SUCCESS 0


//////////////////////////////////////////////////////////////////
/*                            STRUCT		                   */
////////////////////////////////////////////////////////////////

typedef enum e_type
{
    TYPE_NONE   = 0,        // 000000
    COMMAND     = 1 << 0,   // 000001
    PIPE        = 1 << 1,   // 000010
    REDIR_IN    = 1 << 2,   // 000100
    REDIR_OUT   = 1 << 3,   // 001000
    HERE_DOC    = 1 << 4,   // 010000
    APPEND_OUT  = 1 << 5    // 100000
} t_type;

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

typedef struct s_token_management
{
	t_token			*token;
	char **			readed;
}					t_token_manag;

typedef struct s_envp
{
	char			*name;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}				t_envp;



typedef struct s_env_management
{
	bool			sync;
	bool			set;
	t_envp			*envp;
	char			**env;
}					t_env_manag;

typedef struct s_prompt
{
	char			*read_line;
}					t_prompt;

typedef struct s_sig
{
	/* data */
}					t_sig;

typedef struct s_data
{
	int				exit_status;
	t_token_manag	token_manag;
	t_env_manag		envp_manag;
	t_sig			signal;
	t_prompt		prompt;
	// exec;
}					t_data;

//////////////////////////////////////////////////////////////////
//                          PARSING		                       //
////////////////////////////////////////////////////////////////

int 				main(int argc, char **argv, char **env);
int					pars_shell(t_data *data, int argc, char **argv, char **envp);
int					pars_env(t_data *data, char **envp);
int					pars_token(t_data *data);


//////////////////////////////////////////////////////////////////
//                       PARS UTILS		                       //
////////////////////////////////////////////////////////////////

t_envp				*lst_new_envp(char **splited);
int					add_lst(t_data *data, char **splited);
void				free_lst_envp(t_data *data);
int					add_tab(t_data *data, char **envp);
int					split_and_add(t_data *data, char **envp);
int					ft_lstsize_envp(t_envp *lst);
int					uptdate_env(t_data *data);

//////////////////////////////////////////////////////////////////
//                          NOTE		                       //
////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//                          TOOLS		                       //
////////////////////////////////////////////////////////////////


void put_lst_envp(t_envp *envp);

/* 
								NOTE SAMY AND RALPH

	


*/





















/*
	ordre a suivre pour minishell  (fais par Garfi c'est DE CE QUE J'EN AI COMPRIT C'EST PEUT ETRE FAUX !!!!!!!!!!!)

	GROSSO MODO:
		traite l'entree
			-> en faire des tokens pour savoir qu'est ce qui est quoi
			-> les places dans la liste chaine final en fonction des tokens
			-> exec
		structure de la liste chaine:

			la liste chaine est coupe sur des pipes donc:
				0 pipe > 1 noeud
				1 pipe > 2 noeuds
				2 pipe > 3 noeuds
				[...]
			il y a deux int fd in et fd out (attention ! ca peut aussi etre un here doc)
			un tableau de tableau qui comporte la commande a executer (pas forcement dans execve ca peut etre un built-in)

	pour arriver a ce resultat il faudra passer par plusieurs etape

	1) Parseur
		- le parseur sert plusieurs chose:
			1.a) savoir si l'input est correct (comment savoir si une input est bonne ? jsp du tout)

			1.b) arrive a split l'entre en tableau de tableau (par example) pour ensuite les traites de case en case
				donc si mon entre est "echo je suis la >fichier|pwd",
					oui il faut aussi arriver a split quand il y n'a a pas d'espaces,
					il faut que le parseur split en
				case 1 echo
				case 2 je
				case 3 suis
				case 4 la
				case 4 >
				case 5 fichier
				case 2 |
				case 2 pwd

				A quoi ca sert de faire ca ? c'est plus simple d'avoir tout bien organise dans un tableau pour ensuite les lires un part un
				et les traite avec des tokens,
					a quoi sert les tokens ? on verra plus tard chaque chose en son temps



	2) Lexeur
		le lexeurs lui va utiliser le tableau de tableau qui est cree dans la parseurs pour leurs assignes des tokens.

			Pour la tokenisation il y a des token mandatory dont ( a voir si y'en a d'autre )
				- heredoc
				- redirection (> < >> <<) pour savoir comment open le fichier qui est cible  (trunc,
					append, est ce qu'il faut le creer ou pas ...)
				- infile (le nom du fichier qu'il faudra open)
				- outfile (pareil)
					- il faut faire la difference entre infile et outfile et les signes de redirections parce qu'on va open l'infile et l'outfile et non la redirection (c'est evidant mais bon bref ne sait on jamais)
						la redirection sert a savoir comment open le le file quand au file il sert a savoir qu'elle fichier doit etre open
				- pipe ( | )
				- commande (si c'est aucun des autres token alors mettre commande (l'exec fera le tri entre builtin et binaire),
					les options de la commande marche sur le meme fonctionnement)

			Il faut appliquer une regle sur chaque token par example,
			pour l'infile et outfile il faut regarder le signe > >> ou < <<

			le pipe si c'est |

			la commande si c'est aucun des autre token il est place a la fin des if
				/ else if.
			ect pour les autres

			attention quand on applique la regle des redirections il faut faire attention au multiple redirection du genre:
				- echo bonjour > fichier1 > fichier2 >fichier3 dans ce cas la voir comment bash reagit mais l'infile finale peut tres bien changer au file du parsing
				- echo bonjour > fichier1 > fichierSansPermissionsDeLecture > fichier3 > qu'est ce qu'il se passe essayer avec bash ect

	3) Expand
		Attention l'expand se fait juste avant l'exec donc si possible au plus proche de la fonctions d'exec
		L'expand sert a utiliser une variable d'environnement donc si toto=2 dans l'env et que je fais echo $toto alors le $toto devient 2 puis est passer dans a l'exec
	4) exec
*/

#endif