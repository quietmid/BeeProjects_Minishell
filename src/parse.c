/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/12 21:02:22 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_len(t_data *data, int i)
{
	int count;
	t_token	*token;

	count = 0;
	token = data->token;
	while (i < data->arr_len)
	{
		if (token[i].type != PIPE_TOKEN)
			count++;
		else
			break ;
		i++;
	}
	return (count);
}

/*
	may need to create a safe_malloc function that if the result is null return error_msg
*/

//void	array_join(t_data *data)
//{
//	t_parse u;
	 
//	u.i = -1;
//	u.arg_idx = 0;
//	u.token_idx = 0;
//	u.len = cmd_len(data, (u.i + 1));
//	data->argv[u.arg_idx] = (char **)malloc((u.len + 1) * sizeof(char *));
//	while (++u.i < data->arr_len)
//	{
//		//printf("im here\n");
//		if (data->token[u.i].type != PIPE_TOKEN)
//		{
//			data->argv[u.arg_idx][u.token_idx++] = data->token[u.i].input;
//			//printf("array: %d\n", u.i);
//		}
//		else
//		{
//			//printf("a new array\n");
//			if (u.token_idx > 0)
//				data->argv[u.arg_idx++][u.token_idx] = NULL;
//			if (u.arg_idx < data->cmd_count)
//			{
//				u.len = cmd_len(data, (u.i + 1));
//				data->argv[u.arg_idx] = (char **)malloc((u.len + 1) * sizeof(char *));
//				u.token_idx = 0;
//				//printf("a new array\n");
//			}
//		}
//	}
//	if (u.token_idx > 0)
//		data->argv[u.arg_idx][u.token_idx] = NULL; //setting the null for the last group
//}

//void	assign_token(char *input, t_data *data, int i)
//{
//	printf("i: %d\n", i);
//	data->token[i].idx = i;
//	data->token[i].input = input;
//	if (data->token[i].type == 0)
//		data->token[i].type = deter_token_type(input);
//	if (data->token[i].type == 2)
//		data->token[i + 1].type = 11;
//	if (data->token[i].type == 3)
//		data->token[i + 1].type = 8;
//	if (data->token[i].type == 4)
//		data->token[i + 1].type = 9;
//	if (data->token[i].type == 5)
//		data->token[i + 1].type = 10;
//}

//void	init_token(t_data *data, char **str)
//{
//	int i;

//	data->arr_len = ft_arr_len(str);
//	i = 0;
//	while (i < data->arr_len)
//		data->token[i++].type = 0;
//	data->argv = (char ***)malloc((data->cmd_count + 1) * sizeof(char **));
//}

char **redir_argv(char *str)
{
	char **redir;
	int i;
	int x;

	i = 0;
	x = 0;
	redir = ft_calloc(2, sizeof(char **));
	if (!redir)
		return (NULL); //error_msg
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (ft_isredir(str[i]) && str[i] == str[i + 1])
			redir[0] = ft_substr(str, i, 2);
		else if (ft_isredir(str[i]))
			redir[0] = ft_substr(str, i, 1);
	}
	return (redir);
}

t_token assign_token(char *str)
{
	t_token token;
	int i;

	token.cmd = ft_calloc(2, sizeof(char **));
	if (!token.cmd)
		exit (0); //error_msg and exit
	token.redir = ft_calloc(2, sizeof(char **));
	if (!token.redir)
		exit (0); //error_msg and exit
	return (token);
}

char **prompt_prep(char *line)
{
	char	**result;
	int		i;

	i = 0;
	pipe_replace(line);
	result = ft_split(line, 31);
	if (!result)
		return (NULL); //error_msg
	//while (result[i])
	//	pipe_restore(result[i++]);
	return (result);
}
int	parse_start(t_data *data, char *line)
{
	char **input;
	int i;
	
	if (!line || !*line)
		return (1);
	i = 0;
	data->cmd_count = pipe_scans(line);
	//printf("cmd_count: %d\n", data->cmd_count);
	// creates a function that handles the prompt into arrays of string separate by the pipe
	// parse through each of the array and put them in a link list of s_node
	input = prompt_prep(line);
	//int i = 0;
	while (input[i])
		printf("%s\n", input[i++]);
	data->token = ft_calloc(data->cmd_count + 1, sizeof(t_token));
	if (!(data->token))
		return (0); //error_msg
	while (input[i])
	{
		data->token[i].cmd = ft_calloc(2, sizeof(char *));
		if (!(data->token[i].cmd))
			return (0);
		data->token[i].redir = ft_calloc(2, sizeof(char *));
		if (!(data->token[i].redir))
			return (0);
		data->token[i] = assign_token(input[i]);
	}
	ft_free_arr(input);
	// another function that separate these arrays of strings by its location. 
	return (1);
}
