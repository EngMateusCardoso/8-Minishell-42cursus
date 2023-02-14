/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:33:11 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/13 21:03:24 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_env(char *key, char *value)
{
	t_list *pivot;
	char *var;
	char *tmp;
	int len;

	len = ft_strlen(key);
	pivot = g_data.hash_table[hash_function(key) % TABLE_SIZE];
	while (pivot != NULL)
	{
		if (ft_strncmp(((t_env_var *)pivot->content)->key, key, len) == 0)
		{
			ft_free_pointer((void *)&(((t_env_var *)pivot->content)->value));
			((t_env_var *)pivot->content)->value = ft_strdup(value);
			return;
		}
		pivot = pivot->next;
	}
	if (pivot == NULL)
	{
		tmp = ft_strjoin(key, "=");
		var = ft_strjoin(tmp, value);
		insert_in_hashtable(var);
		ft_free_pointer((void *)&var);
		ft_free_pointer((void *)&tmp);
	}
}

void cd_builtin(char *folder)
{
	char	*pwd;
	char	*path;
	char	*cwd;

	if (folder && !(ft_strncmp(folder, "~", 2) == 0))
	{
		if (ft_strncmp(folder, "-", 2) == 0)
		{
			path = find_hash_var(g_data.hash_table[hash_function("OLDPWD") % TABLE_SIZE], "OLDPWD");
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			path = folder;
	}
	else
		path = find_hash_var(g_data.hash_table[hash_function("HOME") % TABLE_SIZE], "HOME");
	if (chdir(path) != 0)
	{
		if (ft_strncmp(folder, "-", 2) == 0)
			error_msg("cd", "OLDPWD not set", 1);
		else
			error_handler(folder, ": ", 1, "cd");
		return;
	}
	pwd = find_hash_var(g_data.hash_table[hash_function("PWD") % TABLE_SIZE], "PWD");
	change_env("OLDPWD", pwd);
	cwd = getcwd(NULL, 0);
	change_env("PWD", cwd);
	ft_free_pointer((void *)&cwd);
	g_data.exit_code = 0;
}
