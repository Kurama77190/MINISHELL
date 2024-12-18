#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define ERROR 1
# define SUCCESS 0

# define ERR_SYN 1
# define ERR_MEM 2
# define ERR_MALLOC "Memory allocation failed"
# define BUFF_SIZE 4096


//////////////////////////////////////////////////////////////////
/*                            STRUCT		                   */
////////////////////////////////////////////////////////////////

typedef enum e_redir_type
{
	NONE,
	IN,
	OUT,
	D_APPEND,
	D_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	key;
	char			*type;
	char			*file_name;
	char			*file_here_doc;
	struct s_redir	*next;
	struct s_redir	*prev;
}					t_redir;

typedef struct s_redir_manag
{
	t_redir			*head;
	t_redir			*current;
}					t_redir_manag;


typedef struct s_token
{
    char            *command;    // Nom de la commande
    char            **args;      // Tableau des arguments
    int             fd_in;       // Descripteur pour redirection d'entrée
    int             fd_out;      // Descripteur pour redirection de sortie
    t_redir_manag	redir_in;    // Nom du fichier d'entrée (si redirection)
    t_redir_manag   redir_out;   // Nom du fichier de sortie (si redirection)
    int             fd_pipe[2];  // Pipe utilisé pour relier la sortie et l'entrée entre commandes
	int				builtin;
	pid_t			pid;
    struct s_token  *next;       // Pointeur vers le prochain nœud
    struct s_token  *prev;       // Pointeur vers le nœud précédent
} 					t_token;

typedef struct s_token_management
{
	t_token			*token;
	t_token			*current_token;
	char			*line;
	char			**readed;
}					t_token_manag;

typedef struct s_envp
{
	char			*name;
	char			*value;
	char			*line;
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;



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

typedef struct s_exec
{

	/*					*/

}					t_exec;


typedef struct s_data
{
	int				exit_status;
	t_token_manag	token_manag;
	t_env_manag		e;
	int				wstatus;
	t_sig			signal;
	t_prompt		prompt;
	int				pipe_fd[2];
	int				fd[2];
	int				stdin_backup;
	int				stdout_backup;
	struct termios	terminal;
	int				nb_levels;
	int				last_pid;
	int				stdin_backup;
	int				stdout_backup;
	int 			free_value;
}					t_data;

extern int			g_exit_status;

//////////////////////////////////////////////////////////////////
//                          BUILTINS			                //
////////////////////////////////////////////////////////////////

/**
 * @file builtins_launch.c
 */
bool				ft_detect_builtin(char **argv, t_data *data);

/**
 * @file builtins_utils.c
 */
void				copy_env(char **envp, t_data *data);
void				copy_env_char(t_data *data);
void				ft_sort_env(t_envp *env);
void				ft_swap_env_lines(t_envp *a, t_envp *b);

/**
 * @file env.c
 */
char				*put_name(char *line);
char				*put_value(char *line);
t_envp				*new_node_env(char *line, t_data *data);
void				push_node_to_env(t_data *data, char *line);
void				ft_env(char **argv, t_data *data);

/**
 * @file export.c
 */
bool				check_double(t_data *data, char *line);
void				ft_exp_env(t_data *data);
bool				check_change_value(t_data *data);
void				ft_export(char **argv, t_data *data);
int					lstadd_envp(t_data *data, char *str);
bool				ft_is_separator(char *s);



/**
 * @file echo.c
 */
void				ft_echo(char **argv, t_data *data);

/**
 * @file pwd.c
 */
void				ft_pwd(t_data *data);

/**
 * @file unset.c
 */
void				search_in_env(t_data *data, char *var);
void				ft_unset(char **argv, t_data *data);
char				*ft_strndup(const char *s, size_t n);

/**
 * @file exit.c
 */
bool				ft_is_number(char *str);
int					ft_value(int value);
void				ft_exit(char **argv, t_data *data);

/**
 * @file cd.c
 */
void				set_env_oldpwd(char *old_pwd, t_data *data);
void				set_env_pwd(char *new_pwd, t_data *data);
void				ft_move_directory(char *path, t_data *data);
void				set_home(t_data *data);
void				ft_cd(char **argv, t_data *data);

//////////////////////////////////////////////////////////////////
//                          EXEC			                    //
////////////////////////////////////////////////////////////////

/**
 * @file exec_cases.c
 */
int					exec_onecommand(char **cmd, t_data *data);
void				ft_multi_pipe(t_token *node, t_data *data, int i);
void				ft_no_pipe(t_token *node, t_data *data);
void				ft_erase_all_temp_here_doc(t_redir *node);

/**
 * @file exec_core.c
 */
char				*ft_path(char *cmd, t_data *data);
void				exec(t_data *data, char **cmd);

/**
 * @file exec_read.c
 */
void				ft_execution(t_data *data);
void				ft_count_levels(t_token *node, int level, t_data *data);

/**
 * @file exec_utils.c
 */
bool				ft_is_delimiter(char *delimiter, char *str);
void				ft_fds_dup2(t_data *data);
bool				is_builtin(char *command);
void				wait_commands(t_data *data);
void				close_hd(t_redir *redir, t_data *data);

/**
 * @file exec_utils_2.c
 */
char				*find_path_to_find(t_data *data);
void				search_index(t_data *data, int *i, char *path);
void				increment_shlvl(t_data *data, int lvl_int);
void				change_shlvl(t_data *data);

/**
 * @file exec_heredoc.c
 */
void				ft_process_heredoc(t_redir *redir, t_data *data);

/**
 * @file exec_redirs_read.c
 */
int					ft_read_heredoc(t_redir *node, t_data *data);
void				ft_read_infile(t_redir *node, t_data *data);
void				ft_read_outfile(t_redir *node, t_data *data);
void				ft_read_redirs(t_token *node, t_data *data);

/**
 * @file exec_redirs.c
 */
void				ft_process_infile(t_redir *current, t_data *data);
void				ft_process_heredoc_file(t_redir *current, t_data *data);
void				ft_exec_redirs(t_token *node, t_data *data);

//////////////////////////////////////////////////////////////////
//                          PARSING		                       //
////////////////////////////////////////////////////////////////

// int 				main(int argc, char **argv, char **env);int	handle_prompt(t_data *data);
void				handle_prompt(t_data *data);
int					check_cmd(t_data *data);
int					pars_shell(t_data *data, int argc, char **argv);
int					pars_env(t_data *data, char **envp);
int					pars_token(t_data *data);
int					setup_token(t_data *data, char *token);
int					setup_cmd(char *token, t_token *new);
int					setup_redir(char *token, t_token *new);
int					add_back_token(t_data *data, t_token *new);
bool				check_redirection(char *str);
bool				check_pipe(char *str);
bool				is_empty_prompt(const char *str);
bool				is_operator(char c);
char				**split_pipes_secure(const char *str);
void				update_in_quote_checker(char c, char *in_quote);
bool				validate_pipe_syntax(char *str, int i);
bool				is_pipe_start_or_end(char *str, int i);
bool				check_double_redirection(char *str, int *i);
bool				check_following_chars(char *str, int *i, int j);
bool				check_unclosed_quotes(const char *str);


//////////////////////////////////////////////////////////////////
//                       ENVIRONMENT	                       //
////////////////////////////////////////////////////////////////

t_envp				*lst_new_envp(char **splited);
int					uptdate_env(t_data *data);
int					ft_lstsize_envp(t_envp *lst);
int					split_and_add(t_data *data, char **envp);
int					add_lst(t_data *data, char **splited);
int					add_tab(t_data *data, char **envp);

//////////////////////////////////////////////////////////////////
//                       	EXPAND		                       //
////////////////////////////////////////////////////////////////

int					pars_expand(t_data *data);
int					ft_expand_redir(char **str, t_envp *env_list);
bool				is_valid_redir(char *str);
bool				is_ambiguous_redir(char *result, char **str);
char				*ft_strjoin_free(char *s1, char *s2, int free_flag);
char				*get_env_value(const char *key, t_envp *envp);
char				*handle_expand_char(char *result, char c);
char				*handle_expand_variable(char *result, char *str, int *i, t_envp *envp);
int					ft_expand_args(char **args, t_envp *envp, int exit_status);
char				*expand_variable_in_str(char *str, t_envp *envp, int exit_status);
char				*expand_dollar(char *str, int *i, t_envp *envp, int exit_status);
char				*join_char_to_str(char *result, char c);
void				remove_quotes(char *str);
void				free_and_shift(char **args, int index);


//////////////////////////////////////////////////////////////////
//                          REDIR		                       //
////////////////////////////////////////////////////////////////

bool				ft_is_operator(char c);
t_redir				*new_redir_in(char *token);
t_redir				*new_redir_out(char *token);
char				*outfile_type(char *token);
char				*infile_type(char *token);
char				*outfile_name(char *token);
char				*infile_name(char *token);
int					add_redir_in(char *token, t_redir_manag *param);
int					add_redir_out(char *token, t_redir_manag *param);
bool				is_operator_in_quotes(char *token, char operator);
void				found_index(char *tmp, int *i);
void				delete_word(char *str, size_t i, unsigned int start);
int					update_in_quote(char c, int in_quote);


//////////////////////////////////////////////////////////////////
//                          CMD 		                       //
////////////////////////////////////////////////////////////////

int					found_cmd_name(char *token, t_token *new);
int					found_args_cmd(char *token, t_token *new);


//////////////////////////////////////////////////////////////////
//                          MEMORY		                       //
////////////////////////////////////////////////////////////////

void				free_token(t_data *data);
void				free_envp(t_data *data);
void				free_redir(t_token *current);
void				ft_free_all(t_data *data, bool free_env);
void				ft_memory(t_data *data);

//////////////////////////////////////////////////////////////////
//                          TOOLS		                       //
////////////////////////////////////////////////////////////////

void put_lst_envp(t_envp *envp);

void				heredoc_sigint_handler(int sig);
void				sigquit_handler(int sig);
void				sigint_handler(int sig);
void				signals(t_data *data);
void				put_lst_envp(t_envp *envp);
void				ft_close_fd(t_data *data, char *msg);
void				ft_error(t_data *data, char *str);
void				ft_error_exit(t_data *data, char *str);
void				ft_free_all_child(t_data *data);
void				ft_error_child(t_data *data, char *msg);



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