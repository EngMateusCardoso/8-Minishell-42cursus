/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:20:17 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 10:50:03 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_builtin(char **cmds)
{
	char	*cmd;
	int		idx;
	int		i;

	if (!cmds[1])
		return ;
	i = 1;
	while (cmds[i])
	{
		cmd = clear_quotes(cmds[i]);
		if (cmd && check_identifier(cmd))
		{
			idx = hash_function(cmd) % TABLE_SIZE;
			if (find_hash_node(cmd))
				delete_from_hashtable(g_data.hash_table[idx], \
				find_hash_node(cmd), cmd);
			g_data.exit_code = 0;
		}
		else
			identifier_error("unset", &cmd);
		i++;
		ft_free_pointer((void *)&cmd);
	}
}

void	delete_from_hashtable(t_list *head, t_list *node, char *key)
{
	int	idx;

	idx = hash_function(key) % TABLE_SIZE;
	if (head == node)
	{
		g_data.hash_table[idx] = g_data.hash_table[idx]->next;
		free_hash_node(node);
		return ;
	}
	while (head)
	{
		if (head->next == node)
		{
			head->next = node->next;
			free_hash_node(node);
			return ;
		}
		head = head->next;
	}
}

void	free_hash_node(t_list *node)
{
	ft_free_pointer((void *)&((t_env_var *)node->content)->key);
	ft_free_pointer((void *)&((t_env_var *)node->content)->value);
	ft_free_pointer(&node->content);
	ft_free_pointer(&node->content);
	ft_free_pointer((void *)&node);
	node = NULL;
	return ;
}
