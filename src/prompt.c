/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:13:43 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/09 13:00:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static void	print_special_prompt(t_shell *shell, char *str)
{
	t_curs			cursor;
	int				n;

	if (ioctl(0, FIONREAD, &n) == 0 && n > 0)
	{
		ft_dprintf(shell->fd_op, "%s%s%s %s[ %s ]%s ", YELLOW, "\xE2\x86\xAA"
			, EOC, !ft_strcmp(get_var_value(get_var(shell->vars,
				SPECIAL_PARAM_QMARK)), "0") ? GREEN : RED, str, EOC);
		return ;
	}
	get_cursor_pos(&cursor);
	if (cursor.col != 1)
		ft_dprintf(shell->fd_op, "%s%%%s\n", INV_COLOR, EOC);
	ft_dprintf(shell->fd_op, "%s%s%s %s[ %s ]%s ", YELLOW, "\xE2\x86\xAA"
		, EOC, !ft_strcmp(get_var_value(get_var(shell->vars,
			SPECIAL_PARAM_QMARK)), "0") ? GREEN : RED, str, EOC);
	if (shell->win.ws_col == 0)
		return ;
	else
	{
		shell->prompt_len = (ft_strlen(str) + 7) % shell->win.ws_col;
		shell->prompt_height = (ft_strlen(str) + 7) / shell->win.ws_col;
	}
}

void		print_prompt(t_shell *shell, int flag)
{
	char	*cwd;
	char	*str;

	if (check_validity(shell))
		return ;
	raw_terminal_mode(shell);
	cwd = getcwd(NULL, MAX_PATH);
	if (!shell->parser.pss || shell->parser.pss->status == PARSER_MORE_INPUT
			|| flag || shell->more_input)
	{
		shell->prompt_len = 2;
		ft_dprintf(shell->fd_op, "%s ", INCOMPLETE_INPUT_PROMPT);
	}
	else
	{
		if (ft_strrchr(cwd, '/') && ft_strchr(cwd, '/') != ft_strrchr(cwd, '/'))
			str = ft_strrchr(cwd, '/') + 1;
		else
			str = cwd;
		print_special_prompt(shell, str);
	}
	free(cwd);
}
