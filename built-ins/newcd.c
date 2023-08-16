/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newcd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/26 11:29:13 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

//cd with nothing go HOME
	//with chdir
//cd with something go
	//with "chdir"
//when CD check OLDPWD and PWD
	//with check_env
//and create OLDPWD & PWD if its necessary
	//add_env (but empty)
//and update if it works
	//with change_env



// Con secret enviroment

// SOLO PARA las variables OLDPWD y PWD (HOME tambien)
	// crear secret enviroment al principio. (igual que enviroment)
	// cd cambia el enviroment si existe y el secret enviroment siempre
	// upset borra el enviroment y setea el secret enviroment a NULL.
	// export setea los 2, secret enviroment y enviroment.
	//limpiar secret enviroment con exit
//
void	check_pwds(t_ms *ms)
{
	if (check_env(ms->env,"PWD") == 1)
		add_env(ms->env, "PWD","");
	if (check_env(ms->env,"OLDPWD") == 1)
		add_env(ms->env, "OLDPWD", "");
}

void	set_pwds(t_ms *ms)
{
	change_env(ms->env, "OLDPWD",get_env_value(ms->env,"PWD"));
	change_env(ms->env, "PWD",getcwd(NULL, PATH_MAX));
}

int cd (t_ms *ms, char **com)
{
	int 	i;

	i = 1;
	if (com[i] == NULL)
		com[i] = get_env_value(ms->env,"HOME");
	if(chdir (com[i]) != 0)
	{
		//perror("");
		ft_exit(1, "cd", com[1], strerror(errno));
		return(1);
	}
	else
	{
		check_pwds(ms);
		set_pwds(ms);
	}
	return(0);
}
