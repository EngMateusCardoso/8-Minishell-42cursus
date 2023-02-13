/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:27:29 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/13 19:11:10 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int hash_function(char *key)
{
    if (*key)
        return (*key + hash_function(key + 1));
    return (0);
}

void insert_in_hashtable(char *envp)
{
    char *key;
    char *value;
    unsigned int hash_index;
    t_env_var *env_var;

    key = ft_substr(envp, 0, ft_strlen(envp) - ft_strlen(ft_strchr(envp, '=')));
    value = ft_substr(ft_strchr(envp, '='), 1, ft_strlen(envp) - (ft_strlen(key) + 1));
    hash_index = hash_function(key) % TABLE_SIZE;
    env_var = (t_env_var *)malloc(sizeof(t_env_var *));
    env_var->key = key;
    env_var->value = value;
    ft_lstadd_back(&(g_data.hash_table[hash_index]), ft_lstnew((void *)env_var));
}

void store_env_variables(char **envp)
{
    if (*envp)
    {
        insert_in_hashtable(*envp);
        store_env_variables(envp + 1);
    }
}

void free_hash_table()
{
    int i;
    t_list *temp;
    t_list *temp2;

    i = 0;
    while (i < TABLE_SIZE)
    {
        temp = g_data.hash_table[i];
        while (temp)
        {
            temp2 = temp->next;
            free(((t_env_var *)temp->content)->key);
            free(((t_env_var *)temp->content)->value);
            free(temp->content);
            free(temp);
            temp = temp2;
        }
        i++;
    }
}

char *find_hash_var(t_list *head, char *key)
{
    t_list *pivot;
    int len;

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
