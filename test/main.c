/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:24:39 by samy              #+#    #+#             */
/*   Updated: 2024/12/15 18:34:07 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // Inclure votre libft pour ft_substr et ft_calloc
#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>





// "<in1"          ___    _________  ls -a ">out1"           ____    __________

int	main(int argc, char **argv)
{
	// char	**result;
	// int		i;

	(void)argc;
	(void)argv;
	int i = ft_countwords("<in1\"          ___    _________  ls -a \">out1\"           ____    __________", 95);
	printf("nombre de mot[%i]\n", i);
	// result = ft_split_args(argv[1], ' ');
	// if (!result)
	// 	return (1);
	// i = 0;
	// while (result[i])
	// {
	// 	printf("Word[%d]: %s\n", i, result[i]);
	// 	free(result[i]);
	// 	i++;
	// }
	// free(result);
	return (0);
}
