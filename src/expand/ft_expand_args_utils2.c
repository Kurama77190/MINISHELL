/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 05:01:13 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/24 05:01:14 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_quotes(t_expand *ctx)
{
	if (ctx->str[ctx->i] == '\'' && !ctx->in_double)
	{
		ctx->in_single = !ctx->in_single;
		ctx->i++;
		return (true);
	}
	if (ctx->str[ctx->i] == '\"' && !ctx->in_single)
	{
		ctx->in_double = !ctx->in_double;
		ctx->i++;
		return (true);
	}
	return (false);
}

static bool	handle_dollar(t_expand *ctx)
{
	char	*tmp;

	if (ctx->str[ctx->i] == '$' && !ctx->in_single && ctx->str[ctx->i + 1])
	{
		tmp = expand_dollar(ctx->str, &ctx->i, ctx->envp, ctx->exit_status);
		ctx->result = ft_strjoin(ctx->result, tmp);
		ft_free((void **)&tmp);
		return (true);
	}
	return (false);
}

char	*expand_variable_in_str(char *str, t_envp *envp, int exit_status)
{
	t_expand	ctx;

	ctx.str = str;
	ctx.result = ft_strdup("");
	ctx.envp = envp;
	ctx.exit_status = exit_status;
	ctx.i = 0;
	ctx.in_single = 0;
	ctx.in_double = 0;
	while (ctx.str[ctx.i])
	{
		if (handle_quotes(&ctx))
			continue ;
		else if (handle_dollar(&ctx))
			continue ;
		else
		{
			ctx.result = join_char_to_str(ctx.result, ctx.str[ctx.i]);
			ctx.i++;
		}
	}
	return (ctx.result);
}
