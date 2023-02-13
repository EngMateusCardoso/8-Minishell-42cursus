/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:17:37 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/12 22:21:23 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_tilde(char *var)
{
	char *home;
	unsigned int idx;

	idx = hash_function("HOME") % TABLE_SIZE;
	if (ft_strncmp(var, "~", 2) == 0)
	{
		home = ft_strdup(find_hash_var(g_data.hash_table[idx], "HOME"));
		return home;
	}
	return NULL;
}

int is_varkey(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

void expand_env_var(char **expand, char *var, int size)
{
	char *key;
	char *value;
	char *tmp;
	unsigned int idx;

	if (size)
	{
		key = ft_substr(var, 0, size);
		idx = hash_function(key) % TABLE_SIZE;
		value = find_hash_var(g_data.hash_table[idx], key);
		if (value != NULL && value[0] != '\0')
		{
			if (*expand == NULL)
				*expand = ft_strdup(value);
			else if (*expand != NULL)
			{
				tmp = *expand;
				*expand = ft_strjoin(tmp, value);
				ft_free_pointer((void *)&tmp);
			}
		}
		ft_free_pointer((void *)&key);
	}
}

int expand_var(char **expanded, char *var)
{
	int size;
	char *value;
	char *temp;

	size = 0;
	if (var[0] == '?')
	{
		value = ft_itoa(g_data.exit_code);
		temp = *expanded;
		*expanded = ft_strjoin(temp, value);
		ft_free_pointer((void *)&temp);
		ft_free_pointer((void *)&value);
		g_data.exit_code = 0;
		return (1);
	}
	else
	{
		while (var[size] && is_varkey(var[size]) && var[size] != '$')
			size++;
		expand_env_var(expanded, var, size);
		return (size);
	}
}

int single_mark_case(char *token, char **expanded)
{
	int i;

	i = 1;
	while (token[i] && token[i] != '\'')
	{
		*expanded = ft_straddchar(*expanded, token[i]);
		i++;
	}
	return (i);
}

int double_mark_case(char *token, char **expanded)
{
	int i;

	i = 0;
	while (token[++i] && token[i] != '\"')
	{
		if (token[i] == '$')
			i += expand_var(expanded, &token[i + 1]);
		else
			*expanded = ft_straddchar(*expanded, token[i]);
	}
	return (i);
}

char *expand_money_sign(char *var)
{
	char *expanded;
	int i;

	expanded = ft_strdup("");
	i = -1;
	while (var[++i])
	{
		if (var[i] == '\'')
			i += single_mark_case(&var[i], &expanded);
		else if (var[i] == '\"')
			i += double_mark_case(&var[i], &expanded);
		else if (var[i] == '$' && is_varkey(var[i + 1]))
			i += expand_var(&expanded, &var[i + 1]);
		else
			expanded = ft_straddchar(expanded, var[i]);
		if (!var[i])
			break;
	}
	if (!expanded)
	{
		ft_free_pointer((void *)&expanded);
		return (NULL);
	}
	return (expanded);
}

char *shrink_asterisks(char *token)
{
	int i;
	char *shrunk;

	i = 0;
	shrunk = NULL;
	while (token[i])
	{
		if (token[i] == '*')
		{
			while (token[i] && token[i] == '*')
				i++;
			shrunk = ft_straddchar(shrunk, '*');
		}
		while (token[i] && token[i] != '*')
			shrunk = ft_straddchar(shrunk, token[i++]);
		if (!token[i])
			break;
	}
	return (shrunk);
}

int find_randon_match(char *str, char *fragment, size_t len, int *index)
{
	int i;

	i = 0;
	if (!str || !fragment)
		return (0);
	while (str[i] && ft_strlen(&str[i]) >= len)
	{
		if (ft_strncmp(&str[i], fragment, len) == 0)
		{
			*index += (i + len);
			ft_free_pointer((void *)&fragment);
			return (1);
		}
		i++;
	}
	ft_free_pointer((void *)&fragment);
	return (0);
}

int unmask_asterisks(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 1)
			str[i] = '*';
	}
	return (1);
}

void mask_asterisks(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
			str[i] = 1;
	}
	return;
}

int match_randon_asterisks(char *str, char *shrunk)
{
	int i;
	size_t len;
	int indexes[2];
	char *fragment;

	i = 0;
	indexes[1] = 0;
	while (shrunk[i])
	{
		len = 0;
		if (shrunk[i] == '*')
			i++;
		indexes[0] = i;
		while (shrunk[i] && shrunk[i] != '*')
		{
			i++;
			len++;
		}
		fragment = ft_substr(shrunk, indexes[0], len);
		if (!find_randon_match(&str[indexes[1]], fragment, len, &indexes[1]))
			return (0 && unmask_asterisks(str));
	}
	return (1);
}

int match_init_asterisk(char *str, char *shrunk)
{
	int i;

	i = 0;
	while (shrunk[i] && shrunk[i] != '*')
		i++;
	if (ft_strncmp(str, shrunk, i) == 0)
		return (1);
	else
		return (0);
}

int match_end_asterisk(char *str, char *shrunk)
{
	int tk_end;
	int n;

	if (!shrunk)
		return (0);
	n = 0;
	tk_end = ft_strlen(shrunk);
	while (shrunk[--tk_end] != '*' && tk_end >= 0)
		n++;
	if (ft_strncmp(&str[ft_strlen(str) - n], &shrunk[tk_end + 1], n) == 0)
		return (1);
	else
		return (0);
}

int match_init_and_end_asterisks(char *str, char *shrunk)
{
	if (!(shrunk[0] == '*') && !match_init_asterisk(str, shrunk))
		return (0 && unmask_asterisks(str));
	if (!(shrunk[ft_strlen(shrunk) - 1] == '*') && !match_end_asterisk(str, shrunk))
		return (0 && unmask_asterisks(str));
	return (1);
}

int has_match(char *str, char *shrunk)
{
	if (ft_strncmp(shrunk, "*", 2) == 0)
		return (1);
	mask_asterisks(str);
	if (!match_init_and_end_asterisks(str, shrunk))
		return (0);
	if (!match_randon_asterisks(str, shrunk))
		return (0);
	return (1 && unmask_asterisks(str));
}

void expand_wildcard(char **new_token, char *token, int *j)
{
	DIR *dir;
	struct dirent *dirent;
	char *shrunk;

	dir = opendir(".");
	shrunk = shrink_asterisks(token);
	if (dir)
	{
		dirent = readdir(dir);
		while (dirent != NULL)
		{
			if (ft_strncmp(dirent->d_name, ".", 1) != 0)
				if (has_match(dirent->d_name, shrunk))
				{
					new_token[*j] = ft_strdup(dirent->d_name);
					*j += 1;
				}
			dirent = readdir(dir);
		}
		closedir(dir);
	}
	if (shrunk != NULL)
		ft_free_pointer((void *)&shrunk);
	return;
}

int has_wildcard(char *var)
{
	int i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '\'')
		{
			while (var[++i] && var[i] != '\'')
				continue;
			if (var[i])
				i++;
		}
		if (var[i] == '\"')
		{
			while (var[++i] && var[i] != '\"')
				continue;
			if (var[i])
				i++;
		}
		if (var[i] == '*')
			return (1);
		if (!var[i])
			break;
	}
	return (0);
}

int can_expand(char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (var[i] && var[i] == '\'')
		{
			i++;
			while (var[i] && var[i] != '\'')
				i++;
		}
		else if (var[i] && var[i] == '\"')
		{
			i++;
			while (var[i] && var[i] != '\"')
				if (var[i++] == '$')
					return (1);
		}
		else if (var[i] && (var[i] == '$' || ft_strncmp(var, "~", 2) == 0))
			return (1);
		if (var[i])
			i++;
	}
	return (0 || has_wildcard(var));
}

void expand_token(char **new_token, char *token, int *j)
{
	char *expanded;

	expanded = NULL;
	if (has_wildcard(token))
		expand_wildcard(new_token, token, j);
	else
	{
		expanded = expand_tilde(token);
		if (expanded == NULL)
			expanded = expand_money_sign(token);
		if (expanded != NULL)
		{
			new_token[*j] = expanded;
			*j += 1;
		}
	}
}

void expand_cmd_and_args(char **new_cmd_and_args, char **cmd_and_args)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd_and_args[i])
	{
		if (can_expand(cmd_and_args[i]))
			expand_token(new_cmd_and_args, cmd_and_args[i], &j);
		else
		{
			new_cmd_and_args[j] = ft_strdup(cmd_and_args[i]);
			j++;
		}
		i++;
	}
	new_cmd_and_args[j] = NULL;
	return;
}

void expand_redirections_and_files(char **new_red_and_fil, char **red_and_fil)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (red_and_fil[i])
	{
		if (can_expand(red_and_fil[i]))
			expand_token(new_red_and_fil, red_and_fil[i], &j);
		else
		{
			new_red_and_fil[j] = ft_strdup(red_and_fil[i]);
			j++;
		}
		i++;
	}
	new_red_and_fil[j] = NULL;
	return;
}

int count_wildcards(char *token)
{
	DIR *dir;
	struct dirent *dirent;
	char *shrunk;
	int i;

	dir = opendir(".");
	i = 0;
	shrunk = shrink_asterisks(token);
	if (dir)
	{
		dirent = readdir(dir);
		while (dirent != NULL)
		{
			if (ft_strncmp(dirent->d_name, ".", 1) != 0)
				if (has_match(dirent->d_name, shrunk))
					i++;
			dirent = readdir(dir);
		}
		closedir(dir);
	}
	ft_free_pointer((void *)&shrunk);
	return (i);
}

int count_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (has_wildcard(args[i]))
			j += count_wildcards(args[i]);
		else
			j++;
		i++;
	}
	return (j);
}

int count_commands(t_cmd *command_table)
{
	int i;
	i = 0;
	while (command_table[i].cmd_and_args || command_table[i].redirections_and_files)
		i++;
	return (i);
}

t_cmd *expand_command_table(t_cmd *command_table)
{
	t_cmd *new_command_table;
	int i;

	i = 0;
	new_command_table = (t_cmd *)malloc(sizeof(t_cmd) * (count_commands(command_table) + 1));
	while (command_table[i].cmd_and_args || command_table[i].redirections_and_files)
	{
		new_command_table[i].cmd_and_args = (char **)malloc(sizeof(char *) * (count_args(command_table[i].cmd_and_args) + 1));
		expand_cmd_and_args(new_command_table[i].cmd_and_args, command_table[i].cmd_and_args);
		new_command_table[i].redirections_and_files = (char **)malloc(sizeof(char *) * (count_args(command_table[i].redirections_and_files) + 1));
		expand_redirections_and_files(new_command_table[i].redirections_and_files, command_table[i].redirections_and_files);
		i++;
	}
	new_command_table[i].cmd_and_args = NULL;
	new_command_table[i].redirections_and_files = NULL;
	return (new_command_table);
}
