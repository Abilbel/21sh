/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:38:05 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/19 13:15:48 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

int	ft_delete(t_shell *shell)
{
	if (shell->line.cursor < shell->line.len && !shell->line.mode)
	{
		shell->line.len--;
		t_puts("dc");
		ft_del_char(shell->line.data, shell->line.cursor);
	}
	return (0);
}
