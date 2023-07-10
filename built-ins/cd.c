/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:59:46 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/10 16:02:17 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


//pruebas para chdir y getcwd()
//  trabajo con directorios


// #include <sys/types.h>
// #include <dirent.h>
// #include <stdlib.h>
// #include <stdio.h>

// int main (int argc, char *argv[]){

//  /* Variables */
//  DIR *dirp;
//  struct dirent *direntp;

//  /* Comprobamos los argumentos */
//  if (argc != 2){
//  printf("Uso: %s directorio\n", argv[0]);
//  exit(1);
//  }

//  /* Abrimos el directorio */
//  dirp = opendir(argv[1]);
//  if (dirp == NULL){
//  printf("Error: No se puede abrir el directorio\n");
//  exit(2);
//  }

//  /* Leemos las entradas del directorio */
//  printf("i-nodo\toffset\t\tlong\tnombre\n");
//  while ((direntp = readdir(dirp)) != NULL) {
//  printf("%llu\t\t%d\t%s\n", direntp->d_ino,  direntp->d_reclen, direntp->d_name);
//  }

//   Cerramos el directorio */
//  closedir(dirp);
// }

//con chdir
//!!!!chdir doesn't change the

int cd (t_env *env,char **com)
{
	int 	i;
	char	*str;

	i = 1;
	if (com[i] == NULL)
	{
		if(chdir (get_env_value(env,"HOME")) != 0)
		{
			perror("chdir() error()");
			return(1);
		}
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment propio
		if (check_env(env, "OLDPWD") == 0)
		{
			change_env(env, "OLDPWD",get_env_value(env, "PWD"));
			str = getcwd(NULL, PATH_MAX);
			if (!str)
				return(2);
			change_env(env, "PWD", str);
		}
		return(0);
	}
	else
	{
		if (chdir (com[i]) != 0)
		{
			perror("chdir() error()");
			return(1);
		}
		//setear el valor de oldpwd del enviroment:oldpwd = pwd del enviroment propio
		if (check_env(env, "OLDPWD") == 0)
		{
			change_env(env, "OLDPWD",get_env_value(env, "PWD"));
			str = getcwd(NULL, PATH_MAX);
			if (!str)
				return(2);
			change_env(env, "PWD", str);
		}
		return(0);
	}


}
/*
cd empty


guarda el path en oldpath
va a home
guarda el nuevo path en path

cd ../   relativo

guarda el path en oldpath
chdir al nuevo directorio
guarda el nuevo path en path

cd /path  ruta absoluta

guarda el path en oldpath
chdir al nuevo directorio
guarda el nuevo path en path

//gcc -Wall -Wextra -Werror cd.c

*/





