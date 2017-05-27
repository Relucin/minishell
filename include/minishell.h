/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:23:30 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/26 16:31:13 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dstruct/ftlist.h>

int		ms_path_check(char **args, t_list *my_environ);
int		ms_builtin_check(char **args, t_list **my_environ);
void	ms_echo(char **args, t_list **my_environ);
void	ms_cd(char **args, t_list **my_environ);
void	ms_setenv(char **args, t_list **my_environ);
void	ms_unsetenv(char **args, t_list **my_environ);
void	ms_env(char **args, t_list **my_environ);
void	ms_exec(char *fpath, char **args, char **env);
char	**ms_list_2darr(t_list *lst);
int		ms_currentpath(char **args, t_list *my_environ);
char	*ms_env_search(char *var, t_list *my_environ);
void	ms_env_update(char *var, char *value, t_list **my_environ);
#endif
