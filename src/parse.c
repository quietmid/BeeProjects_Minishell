/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/05 23:05:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
int empty_line(char *input)
{
	while (ft_isspace(*input))
		input++;
	if (!*input)
		return (1);
	return (0);
}
int ft_ismeta(char c)
{
	if (c == 124 || c == 36 || c == 60 || c == 62)
		return (1);
	return (0);
}
char *find_end(char *str)
{
	while (*str != '\0' && !ft_ismeta(*str) && !ft_isspace(*str))
		str++;
	return (str);
}

int	parse_start(t_data *data, char *line)
//int	parse_start(char *line)
{
	char **result;
	int i = 0;
	
	//if (!line || !*line || empty_line(line))
	//	return (0); // failure
	data->cmd_count = pipe_scans(line);
	printf("%d\n", data->cmd_count);
	space_replace(line);
	result = ft_split(line, 31);
	if (!result)
		return (0);
	while (result[i])
		printf("%s\n", result[i++]);
	// we have splitted the line into arrays of string now we parse each string and assign its token and sequence
	// another function that separate these arrays of strings by its location. 
	// eg. line = echo "hello" 'world' | ls -l | cat grep a > out 
	// group 1 of arrays of strings is
	// echo "hello" 'world' \0
	return (1);
}

//void	parse(t_data *data, const char *line)
//{
//	data->line = ft_split(line, ' ');
//	// if (!data->line)
//	// {
//	// 		"malloc error"? // what if we input NULL?
//	// }
//}
///*
//* execute the cmd, returns 0 on success and -1 when it fails
//*/
//int execute_cmd()
//{
//	return (0);
//}

//int main()
//{
//	char *str = "cat 'hello' | echo hello > hi | hi >> hi;";
//	int d;
//	t_data *data;
	
//	d = parse_start(data, str);
//	return (0);

//}