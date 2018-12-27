/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_comp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:43:13 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:48:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "21sh.h"
#include "libft.h"

static t_redir	*create_redir_comp(char *data)
{
	t_redir		*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = TT_REDIR_R_COMP;
	new_redir->next = NULL;
	new_redir->redir_act = &redir_r_comp;
	new_redir->target = NULL;
	if (ft_isdigit(*data))
	{
		new_redir->in = ft_atoi(data);
		while (ft_isdigit(*data))
			++data;
	}
	new_redir->out = ft_atoi(data + 2);
	return (new_redir);
}

int	rule_redir_r_comp(t_ast_token *list)
{
	t_command	*command;
	t_ast_token	*tmp;
	t_redir		*redir;
	t_redir		*iter;

	redir = create_redir_comp(list->next->data);
	command = ((t_ast *)list->data)->data;
	iter = command->redir_list;
	if (!iter)
		command->redir_list = redir;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = redir;
	}
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}