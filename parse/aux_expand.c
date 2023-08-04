/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:00:23 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/31 16:42:12 by josorteg         ###   ########.fr       */
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

int	ft_one_space(char *str)
{
	int	space_count;
	int	i;

	i = 0;
	space_count = 0;
	while (str[i] != '\0')
	{
	if (str[i] == ' ' && (i == 0 || str[i - 1] != ' '))
		space_count++;
	i++;
	}
	return((int)ft_strlen(str) + space_count + 1);
}

char	*ft_exp_quotes(char *str, int	quot)
{
	int		i;
	char	*result;
	int		j;

	i = 0;
	j = 0;
	result = NULL;
	if (quot == 1)
		return (str);
	else if (quot == 0)
	{
		result = malloc (ft_one_space(str)*sizeof(char));
		while(str[i])
		{
			if (str[i] == ' ' && (i == 0 || str[i - 1] != ' '))
				result[j++] = ' ';
			if (str[i] != ' ')
				result[j++] = str[i];
			i++;
		}

    }
    result[j] = '\0';
    return (result);
}

char	*ft_expand2(t_ms *ms, char *s)
{
	int		i;
	char 	*aux;
	int		count;
	char	*val;
	char	*var;

	i = 0;
	aux = NULL;
	//printf("cadena : %s\n",s);
	while (s[i])
	{
		count = 0;
		while (s[i] != '$' && s[i] != '\0')
			count++;
		i = i + count;
		aux = ft_strjoinfree(aux,ft_substr(s,i - count,count));
		//printf("i:%d count:%d variable1 : %s\n", i, count, aux);
		i++;
		count = 0;
		while (s[i] && (!ft_strchr("\'\" $",s[i])))
		{
			count++;
			if (s[i++] == '?')
				break;
		}
		var = ft_substr(s ,i - count ,count);
		if (var[0] == '?')
			aux = ft_strjoinfree(aux,ft_itoa(g_exit.status));
		else if (check_env(ms->env, var) == 0)
		{
			val = get_env_value (ms->env,var);
			printf("valor : %s\n",val);
			aux = ft_strjoinfree(aux,ft_exp_quotes(val,open_quotes(s,i)));
			printf("valor2 : %s\n",aux);
		}
		else
			aux = ft_strjoinfree(aux,"");
	}

	return(aux);
}
