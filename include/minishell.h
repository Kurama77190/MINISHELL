#ifndef MINISHELL_H
# define MINISHELL_H


enum e_token
{
	INPUT = 0,
	OUTPUT,
	PIPE,
	HERE_DOC,
	COMMAND,
}



/*
	ordre a suivre pour minishell  (fais par Garfi c'est DE CE QUE J'EN AI COMPRIT C'EST PEUT ETRE FAUX !!!!!!!!!!!)

	GROSSO MODO:
		traite l'entree -> en faire des tokens pour savoir qu'est ce qui est quoi -> les places dans la liste chaine final en fonction des tokens -> exec
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
				donc si mon entre est "echo je suis la >fichier|pwd", oui il faut aussi arriver a split quand il y n'a a pas d'espaces, il faut que le parseur split en 
				case 1 echo
				case 2 je
				case 3 suis
 				case 4 la
 				case 4 >
				case 5 fichier
				case 2 |
				case 2 pwd

				A quoi ca sert de faire ca ? c'est plus simple d'avoir tout bien organise dans un tableau pour ensuite les lires un part un 
				et les traite avec des tokens, a quoi sert les tokens ? on verra plus tard chaque chose en son temps



	2) Lexeur
		le lexeurs lui va utiliser le tableau de tableau qui est cree dans la parseurs pour leurs assignes des tokens.
		
			Pour la tokenisation il y a des token mandatory dont ( a voir si y'en a d'autre )
				- heredoc
				- redirection (> < >> <<) pour savoir comment open le fichier qui est cible  (trunc, append, est ce qu'il faut le creer ou pas ...)
				- infile (le nom du fichier qu'il faudra open)
				- outfile (pareil)
					- il faut faire la difference entre infile et outfile et les signes de redirections parce qu'on va open l'infile et l'outfile et non la redirection (c'est evidant mais bon bref ne sait on jamais)
						la redirection sert a savoir comment open le le file quand au file il sert a savoir qu'elle fichier doit etre open
				- pipe ( | )
				- commande (si c'est aucun des autres token alors mettre commande (l'exec fera le tri entre builtin et binaire), les options de la commande marche sur le meme fonctionnement)

			Il faut appliquer une regle sur chaque token par example,
			pour l'infile et outfile il faut regarder le signe > >> ou < <<

			le pipe si c'est |

			la commande si c'est aucun des autre token il est place a la fin des if / else if.
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