/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:34:34 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/13 11:46:15 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	fc_cut_pattern(t_fc *cmd, char *str)
{
	size_t	len_old;
	size_t	len_new;

	len_new = ft_strlen(ft_strchr(str, '=') + 1);
	len_old = ft_strlen(str) - len_new;
	if (!(cmd->old_p = ft_strsub(str, 0, len_old - 1)))
		return (1);
	if (!(cmd->new_p = ft_strsub(str, len_old, len_new)))
		return (1);
	return (0);
}
