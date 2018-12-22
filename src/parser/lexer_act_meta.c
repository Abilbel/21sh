/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_meta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:50:50 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 09:50:50 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int	lexer_add_meta(t_shell *shell, t_token *token, char c)
{
	int	ret;

	(void)shell;
	ret = 0;
	if (add_to_token(token, c))
		ret |= (1 << LEXER_RET_ERROR);
	else if (!set_token_type(token))
	{
		token->len--;
		token->data[token->len] = 0;
		lss_pop(&shell->lexer);
		ret |= (1 << LEXER_RET_CUT);
	}
	else
		ret |= (1 << LEXER_RET_CONT);
	return (ret);
}

int	lexer_create_meta(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_META))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CREATE);
}
