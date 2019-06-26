/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params_expansion_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:23:42 by marin             #+#    #+#             */
/*   Updated: 2019/06/24 08:34:24 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

int	get_special_param_bang(t_shell *shell, char name)
{
	const char	*value;	

	(void)name;
	value = get_var_value(get_var(shell->vars , SPECIAL_PARAM_BANG));
	return (add_string_to_exp_buff(&shell->exp_lexer, value));
}

int	get_special_param_qmark(t_shell *shell, char name)
{
	const char	*value;	

	(void)name;
	value = get_var_value(get_var(shell->vars , SPECIAL_PARAM_QMARK));
	return (add_string_to_exp_buff(&shell->exp_lexer, value));
}