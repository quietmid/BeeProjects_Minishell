/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/11 18:39:53 by jlu              ###   ########.fr       */
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
void	array_join(t_data *data, t_parse *u)
{
	 u->i = -1;
	 u->arg_idx = 0;
	 u->token_idx = 0;
	 u->len = cmd_len(data, u->i + 1);
	 data->argv[u->arg_idx] = (char **)malloc((u->len + 1) * sizeof(char *));
	while (++(u->i) < data->arr_len)
	{
		if (data->token[u->i].type != PIPE_TOKEN)
			data->argv[u->arg_idx][(u->token_idx)++] = data->token[u->i].input;
		else
		{
			if (u->token_idx > 0)
				data->argv[(u->arg_idx)++][u->token_idx] = NULL;
			if (u->arg_idx < data->cmd_count)
			{
				u->len = cmd_len(data, u->i + 1);
				data->argv[u->arg_idx] = (char **)malloc((u->len + 1) * sizeof(char *));
				u->token_idx = 0;
			}
		}
	}
	if (u->token_idx > 0)
		data->argv[u->arg_idx][u->token_idx] = NULL; //setting the null for the last group
}

void	assign_token(char *input, t_data *data, int i)
{
	data->token[i].idx = i;
	data->token[i].input = input;
	if (data->token[i].type == 0)
		data->token[i].type = deter_token_type(input);
	else if (data->token[i].type == 2)
		data->token[i + 1].type = DELIM_TOKEN;
	else if (data->token[i].type == 3)
		data->token[i + 1].type = INFILE_TOKEN;
	else if (data->token[i].type == 4)
		data->token[i + 1].type = OUTFILE_TOKEN;
	else if (data->token[i].type == 5)
		data->token[i + 1].type = OUTFILE_TRUNC_TOKEN;
}

void	init_token(t_data *data, char **str)
{
	int i;

	data->arr_len = ft_arr_len(str);
	i = 0;
	while (i < data->arr_len)
		data->token[i].type = 0;
	data->argv = (char ***)malloc((data->cmd_count + 1) * sizeof(char **));
}

int	parse_start(t_data *data, char *line)
{
	char **result;
	t_parse *utils;
	int i = 0;
	
	utils = data->utils;
	if (!line || !*line)
		return (1);
	data->cmd_count = pipe_scans(line);
	space_replace(line);
	result = ft_split(line, 31);
	if (!result)
		return (0);
	init_token(data, result);
	i = -1;
	while (result[++i])
		assign_token(result[i], data, i);
		//printf("tokened:\n");
		//printf("idx: %d\n", data->token[i].idx);
		//printf("input: %s\n", data->token[i].input);
		//printf("type: %u\n", data->token[i].type);
	array_join(data, utils);
	ft_free_arr(result);
	// another function that separate these arrays of strings by its location. 
	return (1);
}
