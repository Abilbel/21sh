/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_auto.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:23:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/10 17:08:27 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_line.h"
#include "libft.h"

char		*word_to_complete(t_line *line, int flag)
{
	char	*ret;
	int		i;
	char	*buf;

	i = -1;
	if (!(buf = ft_strdup(line->data)))
		return (NULL);
	buf[line->cursor] = 0;
	ret = NULL;
	while (buf[++i])
	{
		if ((buf[i] == ' ' && i > 0 && buf[i - 1] != '\\') || buf[i] == ';'
			|| buf[i] == '>' || buf[i] == '<' || buf[i] == 38 || buf[i] == 124
				|| buf[i] == 39 || buf[i] == 34)
			ret = buf + i;
	}
	if (!ret)
		ret = ft_strdup(buf);
	else if (ret && flag && (*ret == ' ' || *ret == '|' || *ret == ';'
				|| *ret == '&') && *(ret + 1) == 0)
		ret = NULL;
	else if (ret)
		ret = ft_strdup(ret + 1);
	ft_strdel(&buf);
	return (ret);
}

int			is_a_command(t_line *line)
{
	int		ret;
	size_t	i;
	char	c;
	int		prev_word;

	i = 0;
	ret = 1;
	prev_word = -1;
	while ((c = line->data[i]) && i < line->cursor)
	{
		if ((c == ' ' && prev_word == 1) || c == '>' || c == '<')
			ret = 0;
		if (c == ';' || (c == '&' && i > 0 && line->data[i - 1] != '>')
				|| c == '|')
		{
			prev_word = -1;
			ret = 1;
		}
		if (c == '$')
			ret = 2;
		if (ft_isalnum(c) && prev_word < 1)
			prev_word = 1;
		i++;
	}
	return (ret);
}
