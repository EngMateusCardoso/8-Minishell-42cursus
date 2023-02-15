/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:03:17 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/14 22:01:45 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_hashtable(char *name)
{
	char	*key;
	char	*value;

	key = ft_substr(name, 0, ft_strlen(name) - ft_strlen(ft_strchr(name, '=')));
	value = ft_substr(ft_strchr(name, '='), 1, ft_strlen(name) - \
		(ft_strlen(key) + 1));
	change_env(key, value);
	ft_free_pointer((void *)&key);
	ft_free_pointer((void *)&value);
}

void	print_declarex(void)
{
	int		i;
	t_list	*sublist;

	i = 0;
	while (i < TABLE_SIZE)
	{
		sublist = g_data.hash_table[i];
		while (sublist != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(((t_env_var *)(sublist->content))->key, 1);
			ft_putchar_fd('=', 1);
			if (((t_env_var *)(sublist->content))->value)
				ft_putstr_fd(((t_env_var *)(sublist->content))->value, 1);
			ft_putchar_fd('\n', 1);
			sublist = sublist->next;
		}
		i++;
	}
}

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_builtin(char **cmds)
{
	char	*cmd;
	int		i;

	if (!cmds[1])
		print_declarex();
	else
	{
		i = 1;
		while (cmds[i])
		{
			cmd = clear_quotes(cmds[i]);
			if (cmd && check_identifier(cmd))
			{
				if (has_equal(cmd))
					append_hashtable(cmd);
				g_data.exit_code = 0;
			}
			else
				identifier_error("export", &cmd);
			i++;
			ft_free_pointer((void *)&cmd);
		}
	}
}
