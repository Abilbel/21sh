/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 04:54:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "libft.h"

static const t_precedence	g_precedence[] =\
{
	{TT_PIPE, 0},
	{TT_END, 1},
	{TT_OR, 2},
	{TT_AND, 2}
};

static int	precedence(t_ttype type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_precedence) / sizeof(*g_precedence))
	{
		if ((t_ttype)g_precedence[i].type == type)
			return (g_precedence[i].prec);
	}
	return (-1);
}

static int	set_leaves(t_ast *node, t_ast_token **stack)
{
	t_ast_token	*right;
	t_ast_token	*left;

	if (!node)
		return (1);
	if (!(right = pop_ast_token(stack)) || !(left = pop_ast_token(stack)))
	{
		if (right)
		{
			((t_ast *)right->data)->del(right->data);
			free(right);
		}
		free_ast(node);
		return (1);
	}
	node->right = right->data;
	node->left = left->data;
	free(right);
	free(left);
	return (0);
}

void		shunting_yard(t_parser *parser)
{
	while (parser->op_stack
		&& precedence(parser->input_queue->type)
		<= precedence(parser->op_stack->type))
		add_to_ast_token_list(&parser->output_queue,
				pop_ast_token(&parser->op_stack));
	push_ast_token(&parser->op_stack, pop_ast_token(&parser->input_queue));
}

t_ast		*queue_to_ast(t_parser *parser)
{
	t_ast		*ret;
	t_ast_token	*stack;

	stack = NULL;
	while (parser->output_queue)
	{
		if (parser->output_queue->type == TT_OP)
		{
			if (set_leaves(parser->output_queue->data, &stack))
				return (NULL);
		}
		push_ast_token(&stack, pop_ast_token(&parser->output_queue));
	}
	ret = stack->data;
	free(stack);
	return (ret);
}
