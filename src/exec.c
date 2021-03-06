/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:03:28 by gchainet          #+#    #+#             */
/*   Updated: 2019/07/06 15:53:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "jobs.h"
#include "shell.h"
#include "libft.h"
#include "expand.h"
#include "fill_line.h"

static void	exec_internal(t_shell *shell, t_ast *instr,
	const char *prgm, t_builtin builtin)
{
	char	**args;
	char	*path;

	enable_signal(SIGNAL_SIGINT);
	if (prepare_redirs(shell, instr))
		exit(1);
	instr->pid = getpid();
	if (!instr->job->pgid)
		instr->job->pgid = shell->is_subshell ? getppid() : instr->pid;
	setpgid(instr->pid, instr->job->pgid);
	if (!instr->job->async && !shell->is_subshell)
		tcsetpgrp(0, instr->job->pgid);
	enable_signal(SIGNAL_OTHER);
	set_pipeline(shell, instr);
	if (apply_redirs(shell, instr))
	{
		free_shell(shell);
		exit(127);
	}
	args = ((t_command *)instr->data)->args_value;
	if (builtin)
		exit(builtin(shell, args));
	if (!(path = hbt_command(shell, prgm)))
		exit(do_error_handling(prgm));
	exit(execve(path, args, build_env(shell->exec_vars)));
}

int			exec(t_shell *shell, t_ast *instr)
{
	char		*prgm;
	t_builtin	builtin;

	prgm = ((t_command *)instr->data)->args_value[0];
	builtin = is_builtin(prgm);
	if (!builtin)
		hbt_command(shell, prgm);
	if (builtin && !(instr->flags & CMD_FORK) && !instr->job->async)
		instr->ret = exec_builtin(shell, builtin, instr);
	else if ((instr->pid = fork()) == -1)
		return (-1);
	else if (instr->pid == 0)
		exec_internal(shell, instr, prgm, builtin);
	register_proc(instr);
	shell->last_cmd = builtin;
	return (0);
}

/*
** This functions executes a node and adds its processes to the job.
** If job is NULL, it gets created and registered.
*/

int			exec_job(t_shell *shell, t_ast *node, t_job *job)
{
	t_job	*job2;

	job2 = job;
	if (!job2 && !(job2 = new_job()))
		return (-1);
	node->job = job2;
	if (node->exec(shell, node))
		return (-1);
	if (!job && job2->proc)
		set_ret(shell, node, register_job(shell, job2));
	else if (!job)
		free(job2);
	return (0);
}
