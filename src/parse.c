/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/06 18:41:51 by jlu              ###   ########.fr       */
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
	//printf("%d\n", data->cmd_count);
	space_replace(line);
	result = ft_split(line, 31);
	if (!result)
		return (0);
	// init_token
	while (result[i])
		printf("%s\n", result[i++]);
	i = 0;
	while (result[i])
	{
		data->token[i].idx = i;
		data->token[i].input = result[i];
		if (data->token[i].type == 0)
			data->token[i].type = deter_token_type(result[i]);
		if (data->token[i].type == 2)
			data->token[i + 1].type = DELIM_TOKEN;
		if (data->token[i].type == 3)
			data->token[i + 1].type = INFILE_TOKEN;
		if (data->token[i].type == 4)
			data->token[i + 1].type = OUTFILE_TOKEN;
		if (data->token[i].type == 5)
			data->token[i + 1].type = OUTFILE_TRUNC_TOKEN;
		printf("tokened:\n");
		printf("idx: %d\n", data->token[i].idx);
		printf("input: %s\n", data->token[i].input);
		printf("type: %u\n", data->token[i].type);
		i++;
	}
	ft_free_arr(result);
	// another function that separate these arrays of strings by its location. 
	return (1);
}

void	init_token(t_data *data, char **str)
{
	int arr_len;
	int i;

	arr_len = ft_arrlen(str);
	i = 0;
	while (i < arr_len)
		data->token[i].type = 0;
}

t_token_type deter_token_type(char *input)
{
	if (input[0] == '$')
		return (DOLLAR_TOKEN);
	else if (input[0] == '|')
		return (PIPE_TOKEN);
	else if (input[0] == '<' && input[1] == '<')
		return (HERE_DOC_TOKEN);
	else if (input[0] == '>' && input[1] == '>')
		return (REDIR_APP_OUT_TOKEN);
	else if (input[0] == '<')
		return (REDIR_IN_TOKEN);
	else if (input[0] == '>')
		return (REDIR_OUT_TOKEN);
	else if (input[0] == '$')
		return (DOLLAR_TOKEN);
	else
		return (STRING_TOKEN);
	// do we need to check for input[0] == null?
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