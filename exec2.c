/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:59:27 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 21:05:32 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd2(t_cmd *cmd, t_cmd_table *cmd_table)
{
	if (make_heredocs(cmd) == 1)
	{
		free(cmd);
		free(cmd_table);
		return (0);
	}
	return (1);
}

// on redirige vers les fonctions des builtins
void	exec_builtin(t_list *tokens,
					t_list **env,
					int nb_cmds,
					int process_index)
{
	char	*program_name;

	program_name = tokens->content;
	if (ft_strcmp(program_name, "exit") == 0)
		g_msh.exit_status = ft_exit(tokens->next);
	else if (ft_strcmp(program_name, "echo") == 0)
		g_msh.exit_status = ft_echo(tokens->next);
	else if ((ft_strcmp(program_name, "env") == 0) && ft_lstsize(tokens) == 1)
		g_msh.exit_status = ft_env(*env);
	else if (ft_strcmp(program_name, "cd") == 0)
		g_msh.exit_status = ft_cd(tokens->next, env);
	else if (ft_strcmp(program_name, "pwd") == 0)
		g_msh.exit_status = ft_pwd(tokens);
	else if (ft_strcmp(program_name, "export") == 0)
		g_msh.exit_status = ft_export(tokens->next, env);
	else if (ft_strcmp(program_name, "unset") == 0)
		g_msh.exit_status = ft_unset(tokens->next, env);
	if (process_index == nb_cmds - 1)
		g_msh.curr_cmd_table->return_value = g_msh.exit_status;
}

// exec le programme dans le processus enfant
void	exec_program(t_list *lst_tokens, t_cmd_table *cmd_table)
{
	char	**tokens;
	char	**envp;
	long	pid;
	t_list	*new_node;

	tokens = convert_list_to_arr(lst_tokens);
	envp = convert_list_to_arr(g_msh.dup_env);
	pid = fork();
	if (pid < 0)
		quit_prog(EXIT_FAILURE);
	else if (pid == 0)
		exec_child(tokens, envp, cmd_table->nb_cmds, cmd_table->pipes);
	new_node = ft_lstnew((void *)pid);
	if (!new_node)
		quit_prog(EXIT_FAILURE);
	ft_lstadd_back(&cmd_table->pids, new_node);
	free(tokens);
	free(envp);
}

char	**convert_list_to_arr(t_list *lst)
{
	char	**strs;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		strs[i++] = (char *)lst->content;
		lst = lst->next;
	}
	return (strs);
}

// execute processus enfant 
void	exec_child(char **tokens, char **envp, int nb_cmds, int **pipes)
{
	char	*exec_path;

	signal(SIGINT, SIG_DFL);
	close_all_pipes(pipes, nb_cmds);
	if (has_relative_path(tokens[0]) || has_absolute_path(tokens[0]))
	{
		exec_path = ft_strdup(tokens[0]);
		if (!exec_path)
			quit_prog(EXIT_FAILURE);
	}
	else
		exec_path = get_absolute_path(tokens[0]);
	execve(exec_path, tokens, envp);
	if (errno == EACCES)
		write_msh_exec_error(tokens[0], "Permission denied");
	else if (errno == ENOENT && ft_strcmp(tokens[0], "exit") != 0)
		write_msh_exec_error(tokens[0], "command not found");
	free(exec_path);
	free(tokens);
	free(envp);
	if (errno == EACCES)
		exit(EXIT_CMD_INTERRUPTED);
	else if (errno == ENOENT)
		exit(EXIT_CMD_NOT_FOUND);
	exit(errno);
}
