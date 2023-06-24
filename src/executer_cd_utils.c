/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:21:45 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:21:48 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_helper1(char *test)
{
	test = getcwd(NULL, 0);
	if (!test)
		write(2, "cd: error: cannot access parent directories\n", 44);
	free(test);
	g_global.exit_code = 0;
	return ;
}

void	cd_helper2(t_env	*my_list, t_utils *utils)
{
	utils->old = mise_ajour_pwd_before(my_list);
	if (chdir(utils->old) == -1)
		print_errors_cd(0);
	my_pwd(0, my_list);
	g_global.exit_code = 0;
}
