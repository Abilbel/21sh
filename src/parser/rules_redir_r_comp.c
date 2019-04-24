/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_comp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:43:13 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 11:17:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "shell.h"
#include "libft.h"

int				rule_redir_r_comp(t_parser *parser, t_token *list)
{
	(void)list;
	if (create_redir_comp_generic(parser, TT_REDIR_R_COMP, &redir_r_comp))
		return (1);
	return (0);
}
