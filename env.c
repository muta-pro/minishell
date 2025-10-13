/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:38:56 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/11 13:10:14 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*new_env_str(char *key, char *value)
{
	char	*result;
	int		len;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_strcpy(result, key);
	ft_strcat(result, "=");
	ft_strcat(result, value);
	return (result);
}

int	update_env_var(char ***envp, char *key, char *value)
{
	char	*new_var;
	int		i;

	new_var = new_env_str(key, value);
	if (!new_var)
		return ;
	i = find_env_varible(key, value);
	if (i >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = new_var;
	}
	else
		add_env_var(envp, new_var);
}

int	init_shlvl(char **envp)
{
	char	*shlvl_str;
	int		shlvl_value;
	int		i;

	i = 0;
	shlvl_str = NULL;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "SHLVL=", 6) == 0)
		{
			shlvl_str = (*envp)[i] + 6;
			break ;
		}
		i++;
	}
	if (shlvl_str)
		shlvl_value = ft_atoi(shlvl_str);
	else
		shlvl_value = 0;
	shlvl_value++;
	update_env_var(&envp, "SHLVL", ft_itoa(shlvl_value));
}

char	*get_env_var(char **envp, char *key);//read var value
void	unset_env_var(char ***envp, char *key);//remove var
char	**copy_envp(char **envp);//dup env
void	**free_envp(char **envp);//cleanup
int	find_env_varible(char **envp, char *key);
