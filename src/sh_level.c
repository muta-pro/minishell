/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_level.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:38:56 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/01 17:24:11 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "shell.h"


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
