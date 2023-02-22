/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:27:29 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/22 14:42:39 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

unsigned int	hash_function(char *key)
{
	if (*key)
		return (*key + hash_function(key + 1));
	return (0);
}

char	*find_hash_var(t_list *head, char *key)
{
	t_list	*pivot;
	int		len;

	len = ft_strlen(key);
	pivot = head;
	while (pivot != NULL)
	{
		if (ft_strncmp(((t_env_var *)pivot->content)->key, key, len) == 0)
			return (((t_env_var *)pivot->content)->value);
		pivot = pivot->next;
	}
	return (NULL);
}

t_list	*find_hash_node(char *key)
{
	t_list	*pivot;
	int		len;
	int		i;

	len = ft_strlen(key);
	i = hash_function(key) % TABLE_SIZE;
	pivot = g_data.hash_table[i];
	while (pivot != NULL)
	{
		if (ft_strncmp(((t_env_var *)pivot->content)->key, key, len) == 0)
			return (pivot);
		pivot = pivot->next;
	}
	return (NULL);
}
