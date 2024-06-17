/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:42:45 by jlu               #+#    #+#             */
/*   Updated: 2024/06/17 15:53:23 by jlu              ###   ########.fr       */
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
			num_redir += 2;
			i += 2;
		}
		else if (ft_isredir(str[i]))
		{
			num_redir += 2;
			i++;
		}
		else
			i++;
	}
	return (num_redir);
}
char **redir_argv(char *str)
{
	char **redir;
	int i;
	int x;
	int len;

	len = calcu_redir(str);
	printf("how many redir: %d\n", len);
	if (len == 0)
		return (NULL);
	i = 0;
	x = 0;
	redir = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!redir)
		return (NULL); //error_msg
	len = 0;
	while (str[i])
	{
		if (ft_isredir(str[i]))
		{
			if (str[i + 1] == str[i])
			{
				redir[len++] = ft_substr(str, i, 2);
				i += 2;
			}
			else
			{
				redir[len++] = ft_substr(str, i, 1);
				i++;
			}
			while (ft_isspace(str[i]))
				i++;
			x = i;
			while (!ft_isspace(str[i]) && !ft_isredir(str[i]) && str[i])
				i++;
			if (i > x)
				redir[len++] = ft_substr(str, x, i - x);
		}
		else
			i++;
	}
	if (len == 0)
		return (NULL);
	redir[len] = NULL;
	return (redir);
}

char **cmd_argv(char *str)
{
	char **temp;
	char **cmd;
	int len;
	int i;
	int j;

	space_replace(str);
	temp = ft_split(str, 31);
	if (!temp)
		return (NULL);
	len = ft_arr_len(temp);
	cmd = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!cmd)
	{
		ft_free_arr(temp);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (temp[i])
	{
		if (ft_isredir(temp[i][0]))
		{
			i++;
			if (temp[i])
				i++;
		}
		else
		{
			cmd[j] = ft_strdup(temp[i]);
			j++;
			i++;
		}
	}
	cmd[j] = NULL;
	ft_free_arr(temp);
	return (cmd);
}

//t_token assign_token(char *str, int i)
//{
//	t_token token;

//	token.idx = i;
//	token.redir = redir_argv(str);
//	token.cmd = cmd_argv(str);
//	return (token);
//}

/* for linked list*/

static t_token *find_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}
/* linked list ver */
void assign_token(t_token **token, char *str, int i)
{
	t_token *node;
	t_token *last_node;

	if (!token)
		return ; //error_msg
	node = malloc(sizeof(t_token));
	if (!node)
		return ; // error_msg
	node->next = NULL;
	node->idx = i;
	node->redir = redir_argv(str);
	node->cmd = cmd_argv(str);
	if (!token)
		*token = node;
	else
	{
		last_node = find_last(*token);
		last_node->next = node;
	}
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
	return (result);
}

static void print_redir_argv(char **redir)
{
	int i;

	i = 0;
	if (!redir)
		return ;
	while (redir[i])
	{
        printf("redir: %s\n", redir[i]);
		i++;
    }
}

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
//int	parse_start(t_data *data, char *line)
//{
//	char **input;
//	int i;
	
//	if (!line || !*line)
//		return (1);
//	i = 0;
//	data->cmd_count = pipe_scans(line);
//	//printf("cmd_count: %d\n", data->cmd_count);
//	input = prompt_prep(line);
//	while (input[i])
//		printf("%s\n", input[i++]);
//	data->token = ft_calloc(data->cmd_count, sizeof(t_token));
//	if (!(data->token))
//		return (0); //error_msg
//	i = 0;
//	// this is not how linked list work, i am still focusing on using an idx
//	while (input[i])
//	{
//		printf("%s\n", input[i]);
//		data->token[i] = assign_token(input[i], i);
//		//if (i < data->cmd_count)
//		//	data->token[i].next = &data->token[i + 1];
//		//else
//		//	data->token[i].next = NULL;
//		//printf("token idx: %d \n", data->token[i].idx);
//		// debug
//		print_redir_argv(data->token[i].redir);
//		print_cmd_argv(data->token[i].cmd);
//		i++;
//	}
//	ft_free_arr(input);
//	//i = 0;
//	//int x = 0;
//	//while (i < data->cmd_count)
//	//{
//	//	printf("token idx: %d \n", data->token[i].idx);
//	//	while (data->token[i].redir[x])
//	//		printf("%s\n", data->token[i].redir[x++]);
//	//	x = 0;
//	//	while (data->token[i].cmd[x])
//	//		printf("%s\n", data->token[i].cmd[x++]);
//	//	//print_redir_argv(data->token[i].redir);
//	//	//print_cmd_argv(data->token[i].cmd);
//	//	i++;
//	//}
//	// another function that separate these arrays of strings by its location. 
//	return (1);
//}
/*
	linked list ver
*/
int	parse_start(t_data *data, char *line)
{
	char **input;
	t_token *token;
	int i;
	
	if (!line || !*line)
		return (1);
	i = 0;
	data->cmd_count = pipe_scans(line);
	input = prompt_prep(line);
	//while (input[i]) //debug
	//	printf("%s\n", input[i++]);
	token = malloc(sizeof(t_token));
	if (!token)
		return (0); //error_msg
	i = 0;
	while (input[i])
	{
		//printf("%s\n", input[i]);
		assign_token(&token,input[i], i);
		i++;
	}
	while (token->next)
	{
		print_redir_argv(token->redir);
		print_cmd_argv(token->cmd);
		token = token->next;
	}
	ft_free_arr(input);
	// another function that separate these arrays of strings by its location. 
	return (1);
}