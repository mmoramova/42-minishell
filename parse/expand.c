/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:44:22 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/26 11:30:59 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_strjoinfree(char *s1, char const *s2)
{
	int		j;
	int		i;
	char	*p;

	if (!s1)
		return((char *)s2);
	if (!s2)
		return(s1);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2[++j])
		p[i + j] = s2[j];
	p[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (p);
}

char	*ft_expand (t_ms *ms, char *s)
{
	int		i;
	char	*aux;
	int		count;
	char	*val;
	char	*var;

	i = 0;

	aux = NULL;
	while (s[i] !='$' && s[i] != '\0')
		i++;
	aux = ft_substr(s,0,i);
	while (s[i])
	{
		//here we need to do if its $? then change it for global variable

		if (s[i] == '$' && (open_quotes(s,i) != 2))
		{
			i++;
			count = 0;

			while (!ft_strchr("\'\" $",s[i]) && s[i])
			{
				count++;
				//printf("len var=%d",count);
				i++;
			}
			var = ft_substr(s ,i - count ,count);
			//printf("Before join aux=%s var=%s\n", aux, var);
			if (check_env(ms->env, var) == 0)
			{
				val = get_env_value (ms->env,var);
				//printf("\nvariable:%s valor:%s\n\n",var, val);
				//res = malloc(ft_strlen(s) - ft_strlen(var) + ft_strlen(val));
				//printf("Before join aux=%s var=%s       val=%s\n", aux, var, val);
				aux = ft_strjoinfree(aux,val);
			}
			else
				aux = ft_strjoinfree(aux,"");
		}
		count = 0;
		while ((s[i] !='$' || (s[i] == '$' &&  (open_quotes(s,i) == 2))) && s[i] != '\0')
		{
			count++;
			i++;
		}
		aux = ft_strjoinfree(aux,ft_substr(s,i - count,count));
	}
	//printf("at the end aux=%s var=%s\n", aux, var);
	return (aux);
}
