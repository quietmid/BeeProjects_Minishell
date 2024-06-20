 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/18 20:42:54 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calcu_redir(char *str)
{
	int i;
	int num_redir;

	i = 0;
	num_redir = 0;
	while (str[i])
	{
		if (ft_isredir(str[i]) && str[i + 1] == str[i])
		{
			num_redir += 1;
			i += 2;
		}
		else if (ft_isredir(str[i]))
		{
			num_redir += 1;
			i++;
		}
		else
			i++;
	}
	return (num_redir);
}

int	extract_redir(char *str, char **redir, int i)
{
	if (str[i + 1] == str[i])
	{			
		redir[0] = ft_safe_substr(str, i, 2);
		i += 2;			
	}
	else
	{
		redir[0] = ft_safe_substr(str, i, 1);
		i++;
	}
	return (i);
}
char ***redir_argv(char *str, int len, char ***redir)
{
	int i;
	int x;

	i = 0;
	x = 0;
	len = 0;
	while (str[i])
	{
		if (ft_isredir(str[i]))
		{
			i = extract_redir(str, redir[len], i);
			while (ft_isspace(str[i]))
				i++;
			x = i;
			while (!ft_isspace(str[i]) && !ft_isredir(str[i]) && str[i])
				i++;
			if (i > x)
				redir[len][1] = ft_safe_substr(str, x, i - x);
			redir[len++][2] = NULL;
		}
		else
		i++;
	}
	redir[len] = NULL;
	return (redir);
}
int		extract_cmd(char **temp, int i)
{
	i++;
	if (temp[i])
		i++;
	return (i);
}

char **cmd_argv(char **temp, int len)
{
	char **cmd;
	int i;
	int j;

	cmd = (char **)ft_safe_calloc((len + 1), sizeof(char *));
	i = 0;
	j = 0;
	while (temp[i])
	{
		if (ft_isredir(temp[i][0]))
			i = extract_cmd(temp, i);
		else if (i > 0 && !(ft_isredir(temp[i - 1][0])) && temp[i])
			cmd[j++] = ft_strdup(temp[i++]);
		else if (i == 0 && !ft_isredir(temp[i][0]))
			cmd[j++] = ft_strdup(temp[i++]);
		else
		{
			i++;
			j++;
		}
	}
	cmd[j] = NULL;
	ft_free_arr(temp);
	return (cmd);
}

t_token assign_token(char *str, int i)
{
	t_token token;
	char **temp;
	int len;
	int x;

	token.idx = i;
	len = calcu_redir(str);
	token.redir = (char ***)ft_safe_malloc((len + 1) * sizeof(char **));
	x = 0;
	while (x < len)
	{
		token.redir[x] = (char **)ft_safe_calloc(3, sizeof(char *)); //need a final safe way to free everything tho
		x++;
	} 
	if (len == 0)
		token.redir[0] = NULL; 
	else
		token.redir = redir_argv(str, len, token.redir);
	temp = prompt_prep(str, 0);
	len = ft_arr_len(temp);
	token.cmd = cmd_argv(temp, len);
	return (token);
}

char **prompt_prep(char *line, int opt)
{
	char	**result;

	if (opt == 1)
		pipe_replace(line);
	else
		space_replace(line);
	result = ft_split(line, 31);
	if (!result)
		error_msg("prompt split failed");
	return (result);
}
// debug
static void print_redir_argv(char ***redir)
{
	int i;

	i = 0;
	if (!redir)
		return ;
	while (redir[i])
	{
		printf("redir [%d] \n", i);
        printf("redir dir: %s\n", redir[i][0]);
        printf("redir fd: %s\n", redir[i][1]);
		i++;
    }
}
// debug
static void print_cmd_argv(char **redir)
{
	int i;
    for (i = 0; redir[i] != NULL; i++)
    {
        printf("cmd: %s\n", redir[i]);
    }
}
/* 
Starts parsing the input and store them as redir and/or cmd. Each token represent the prompt in between the pipes
*/
int	parse_start(t_data *data, char *line)
{
	char **input;
	int i;
	
	i = 0;
	data->cmd_count = pipe_scans(line);
	input = prompt_prep(line, 1);
	//debug
	while (input[i])
		printf("%s\n", input[i++]);
	//debug
	data->token = ft_safe_calloc(data->cmd_count, sizeof(t_token));
	i = 0;
	while (input[i])
	{
		data->token[i] = assign_token(input[i], i);
		//debug
		printf("%s\n", input[i]);
		printf("token idx: %d \n", data->token[i].idx);
		print_redir_argv(data->token[i].redir);
		print_cmd_argv(data->token[i].cmd);
		//debug
		i++;
	}
	ft_free_arr(input);
	data->hd = check_heredoc(data);
	// debug
	printf("here_doc in token[%d]\n", data->hd);
	// debug
	// now iterates through the token and check redir for here_doc
	
	return (1);
}


/* without debuggers*/
// int	parse_start(t_data *data, char *line)
// {
// 	char **input;
// 	int i;
	
// 	data->cmd_count = pipe_scans(line);
// 	input = prompt_prep(line, 1);
// 	data->token = ft_safe_calloc(data->cmd_count, sizeof(t_token));
// 	i = 0;
// 	while (input[i])
// 		data->token[i] = assign_token(input[i++], i);
// 	ft_free_arr(input);
// 	data->hd = check_heredoc(data);
// 	// now iterates through the token and check redir for here_doc
// 	return (1);
// }

