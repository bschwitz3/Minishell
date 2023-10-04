/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 01:24:15 by snadji-h          #+#    #+#             */
/*   Updated: 2023/01/12 21:15:47 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/errno.h>
# include "libft/libft.h"

# define TRUE 1
# define FALSE 0

# define MAX_PATH 1024

# define CTRL_D 4
# define CTRL_C 3
# define ENTER_KEYCAP 10
# define CTRL_B 28

# define EXIT_GENERAL_ERROR 2
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_INTERRUPTED 130
# define EXIT_ERROR_FORMAT 258

# define WHITE_SPACE " \t\n\v\f\r"

//tunning couleur
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

typedef char	t_bool;

/* nouvelle base */
typedef struct s_base
{
	t_list	*cmd_tables;
}	t_base;

/* tableau de commandes */
// liste de cmds
// nb de cmds simple dans la liste
// tab d'int, chaque changement de dimension = pipe
// liste des PID, font la queue
// il y aura aussi la variable globale et l'exit_status,
// suite : mais c'est pour pas ignorer les bultins. ex : "sleep 5 | cd ta_mere"
typedef struct s_cmd_table
{
	t_list	*cmds;
	int		nb_cmds;
	int		**pipes;
	t_list	*pids;
	int		return_value;
}	t_cmd_table;

/* une SEULE cmd et potentiellement argument(s) */
// liste des elements de la cmd
// liste des redir sur cette cmd
typedef struct s_cmd
{
	t_list	*tokens;
	t_list	*redirs;
}	t_cmd;

/* UNE redirections sur UNE cmd */
// nom du fichier vers lequel rediriger
// type de redir > , < , >> , << 
typedef struct s_redir
{
	char	*direction;
	char	type[2];
}	t_redir;

/* stuct global qui carry tous les data du program */
// chaine d'entrée
// base
// liste des variable env
// status de sortie de la dernière cmd
// pointe vers la comande en execution, utile quand le nom du prog
// suite : de sortie est utilisé en parallèle par d'autre cmd
typedef struct s_msh
{
	char		*input;
	t_base		*base;
	t_list		*dup_env;
	int			exit_status;
	t_cmd_table	*curr_cmd_table;
	t_redir		*redir;
}	t_msh;

t_msh			g_msh;

// -- signal.c --
void		catch_sigint(int signum);
void		catch_sigquit(int signum);

// -- quit.c --
void		free_msh(t_msh *msh);
void		free_base(t_base *base);
void		free_cmd_table(void *cmd_table);
void		free_cmd(void *cmd);
void		free_redir(void *redir);

// -- quit2.c --
void		quit_prog(int exit_status);

// -- env.c --
void		dupli_env(t_list **dup_env, char **envp);
void		save_last_token(t_cmd_table *cmd_table);
char		*convert_to_path(char *token);
void		update_environment_var(char *var, char *new_value, t_list *env);
char		*replace_env_value(char **env_ptr, char	*var_name, char *new_value);

// -- env2.c --
t_list		*get_split_token(char *token);
void		replace_tilde_with_home(char **token);
void		tilde_join(char **str, char **home_path);
void		replace_one_var(char **str);
void		replace_vars_with_values(char **str);

// -- env3.c --
int			has_only_one_cmd(void);
void		replace_envs(t_list **tokens, t_list *redirs);
void		replace_env_single_token(char **token);

// -- env4.c --
char		*get_var_name(char *str);
char		*get_last_exec_name(char *underscore);
char		*replace_midstring(char *original,
				char *old_substr,
				char *new_substr,
				int replace_i);
void		replace_status_env(char **str, int last_status);
int			ft_strnstr_iterator(char *haystack, char *needle, size_t len);

// -- env5.c --
char		*join_split_token(t_list *split_token);
int			get_new_token_size(t_list *split_token);
int			is_token_empty(void *data);
int			is_env_var(char *potential_var, t_list *env);
void		unset_oldpwd(void);

// -- env6.c --
void		remove_env_value(char	*key);
void		replace_string(char *src, char **dest);
void		increment_shlvl(void);

// -- prompt.c --
char		*write_prompt(void);

// -	- get_input.c --
int			get_input(void);
int			check_input(char *input);
int			is_input_valid_unexpected_token(char *input, char *err_msg);
int			is_input_valid_not_supported(char *input, char *err_msg);

// -- input_utils.c --
int			has_quotes_open(char *input, char *err_msg);
int			has_char_at_beginning(char *input, char c, char *err_msg);
int			has_char_at_end(char *input, char c, char *err_msg);
int			has_forbidden_sequence(char *input, char *test, char *err_msg);
int			has_spaces_between_char(char *input, char c, char *err_msg);

// -- input_utils2.c --
int			has_non_supported(char *input, char *test, char *err_msg);
int			has_non_supported_one(char *input, char *test, char *err_msg);

// -- parse_utils.c --
void		skip_quotes(const char *input, int *curr_pos);
void		skip_spaces(const char *input, int *curr_pos);
char		*ft_strstr_quotes(char *str, char *to_find);
int			is_quote(char c);
void		skip_letters(const char *input, int *curr_pos);

// --parse_utils2.c --
int			is_token_delimiter(char c);
int			is_path_executable(char *exec_file);
void		delete_quotes(char *token);
int			is_cmd_delimiter(char c);

// -- error_msg.c --
void		write_msh_error(char *err_msg);
void		write_msh_exec_error(char *exec_name, char *err_message);
void		write_msh_exec_arg_error(char *exec_name,
				char *arg, char *err_message);

// -- parse.c ---
t_base		*get_base(void);
t_cmd_table	*get_cmd_table(int *curr_pos);
t_cmd		*get_cmd(int *curr_pos);
char		*get_token(int *curr_pos);
t_redir		*get_redir(int *curr_pos);

// -- exec.c ---
void		exec_base(t_base *base);
void		exec_cmd_table(t_cmd_table *cmd_table);
int			has_relative_path(char *first_token);
int			has_absolute_path(char *first_token);
void		exec_cmd(t_cmd *cmd, t_cmd_table *cmd_table, int process_index);

// -- exec2.c --
int			exec_cmd2(t_cmd *cmd, t_cmd_table *cmd_table);
void		exec_builtin(t_list *tokens,
				t_list **env,
				int nb_cmds,
				int process_index);
void		exec_program(t_list *lst_tokens, t_cmd_table *cmd_table);
char		**convert_list_to_arr(t_list *lst);
void		exec_child(char **tokens, char **envp, int nb_cmds, int **pipes);

// -- exec3.c --
char		*get_absolute_path(char *program_name);
char		**get_path_env_split(void);
void		add_slash(char ***path_env_split);
char		*get_correct_path(char *program_name, char **path_env_split);
void		exec_parent(t_list **pids);

// -- pipe.c --
int			**init_pipes(int nb_cmds);
void		close_all_pipes(int **pipes, int nb_cmds);
int			set_redirs_pipes(t_list *redirs,
				t_cmd_table *cmd_table,
				int process_index);
int			has_redirs(t_list *redirs, char *type);
int			open_all_files(t_list *redirs);

// -- pipe2.c --
int			open_file(t_redir *redir, int prev_fd,
				int flags, mode_t permissions);

// -- builtins.c --
int			is_builtin(t_list *tokens);

// -- ft_exit.c --
int			ft_exit(t_list *args);

// -- ft_echo.c -- 
int			ft_echo(t_list *tokens);
int			has_repeated_char_in_str(char repeat_chr, char *str,
				unsigned int start);

// -- ft_env.c --
int			ft_env(t_list *env);

// -- ft_cd.c --
int			ft_cd(t_list *tokens, t_list **env);
int			only_cd_errors(t_list *tokens);
int			cd_env_error_check(char *env);
int			cd_error_messsage(char *builtin, char *error);
int			other_invalid_error(char *builtin, int error, char *arg);

// -- ft_cd2.c --
int			has_x_permission(char *path);
int			cd_path_error_check(char *path);
int			execute_cd(t_list *tokens, t_list **env, char *pwd);

// -- ft_cd3.c --
int			change_dir_home(char *cur_pwd, t_list **env);
int			change_to_old_dir(char *cur_pwd, t_list **env);
int			update_directories(char *old_dir, t_list **env);
void		create_environment_var(char *token_str, t_list **env);

// -- ft_pwd.c --
int			ft_pwd(t_list *tokens);

// -- ft_export.c --
int			ft_export(t_list *tokens, t_list **env);
void		print_all_exported_vars(t_list *env);
t_list		*get_sorted_env(t_list *env);
int			has_valid_identifier_export(char *token_str);
int			is_token_valid_export(char *token_str, char *err_message);

// -- ft_export2.c --
void		update_env_var_with_token(char *token_str, char *var, t_list *env);
char		*get_value_name(char *str);

// -- ft_unset.c --
int			ft_unset(t_list *tokens, t_list **env);
void		delete_env_var(char *var, t_list **env);
int			has_valid_identifier_unset(char *token_str);
int			is_token_valid_unset(char *token_str, char *err_message);
void		ft_lstdel_node_nbr(t_list **lst, int node_nbr, void (*del)(void*));

// -- ft_unset2.c --
void		ft_delete_list_str(void *data);

// -- heredoc.c --
int			make_heredocs(t_cmd *cmd);
int			check_heredoc(t_cmd *cmd);
int			redir_heredoc(t_cmd *cmd);
void		heredoc(char *limiter, int *fd);
void		nothing(int signal);

// -- heredoc2.c -- 
void		stop_heredoc(int signal);
void		newline(int signal);

#endif
