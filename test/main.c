/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:24:39 by samy              #+#    #+#             */
/*   Updated: 2024/12/22 01:54:33 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // Inclure votre libft pour ft_substr et ft_calloc
#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>




// "<in1"          ___    _________  ls -a ">out1"           ____    __________

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	char	**args = ft_split(argv[1], ' ');
	if (execve(args[0], args, envp) != 0)
	{
		printf("ERROR\n");
	}
	return (0);
}

// echo -n -n -n -n ne marche pas.
// export TEST=123 les variables ne update plus.
//