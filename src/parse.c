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
	char q;

	q = 0;
	i = 0;
	num_redir = 0;
	while (str[i])
	{
		q = quote_finder(str[i], q);
		if (ft_isredir(str[i]) && str[i + 1] == str[i] && !q)
		{
			num_redir += 1;
			i += 2;
		}
		else if (ft_isredir(str[i]) && !q)
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
	char q;

	i = 0;
	x = 0;
	len = 0;
	q = 0;
	while (str[i])
	{
		q = quote_finder(str[i], q);
		if (ft_isredir(str[i]) && !q)
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
	if ((ft_isredir(temp[i][1]) && !temp[i][2]) || !temp[i][1])
	{
		i++;
		if (temp[i])
			i++;
	}
	else if (!ft_isredir(temp[i][ft_strlen(temp[i])]))
		i += 1;
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
		else if (i > 0 && ((!(ft_isredir(temp[i - 1][0])) && temp[i]) || (!ft_isredir(temp[i - 1][ft_strlen(temp[i - 1])]))))
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

void	assign_token(char *str, t_token *t)
{
	char **temp;

	temp = NULL;
	if (str && *str != '\0')
	{
		if (t->redir_len != 0) 
			t->redir = redir_argv(str, t->redir_len, t->redir);
		temp = prompt_prep(str, 0);
		t->cmd_len = ft_arr_len(temp);
		t->cmd = cmd_argv(temp, t->cmd_len);
		t->cmd_len = ft_arr_len(t->cmd);
	}
	else
		(void)t ;
}

char **prompt_prep(char *line, int opt)
{
	char	**result;

	if (opt == 1)
		pipe_replace(line);
	else
		space_replace(line);
	result = ft_split(line, 31);
	if (!result) // err msg?
		error_msg("prompt split failed");
	return (result);
}

// // // debug
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

static void print_cmd_argv(char **redir)
{
	int i;
	if (!redir)
		return ;
    for (i = 0; redir[i] != NULL; i++)
    {
        printf("cmd: %s\n", redir[i]);
    }
}

t_token	init_token(char *str, int i)
{
	t_token t;
	int	x;

	t.hd = 0;
	t.idx = i;
	t.redir_len = calcu_redir(str);
	if (t.redir_len > 0)
		t.redir = (char ***)ft_safe_malloc((t.redir_len + 1) * sizeof(char **));
	x = -1;
	while (++x < t.redir_len)
		t.redir[x] = (char **)ft_safe_calloc(3, sizeof(char *));
	if (t.redir_len == 0)
		t.redir = NULL;
	return (t);
}

/* 
Starts parsing the input and store them as redir and/or cmd. Each token represent the prompt in between the pipes
*/
	/*
	NEED to re sequence my parser. Split by pipe, expand, and the split by space
	second, I need to make sure I expand properly when there is just one $ 
	*/
int	parse_start(t_data *data, char *line)
{
	char **input;
	int i;
	
	i = 0;
	data->cmd_count = pipe_scans(line);
	input = prompt_prep(line, 1);
	// data->token = ft_calloc(data->cmd_count, sizeof(t_token));
	data->token = malloc(sizeof(t_token) * data->cmd_count);
	if (!data->token)
		return (0);
	i = 0;
	while (input[i])
	{
		data->token[i] = init_token(input[i], i);
		printf("token addr before: %p\n", &data->token[i]);
		input[i] = check_expand(input[i], data);
		assign_token(input[i], &data->token[i]);
		data->hd += check_heredoc(&data->token[i]);
		ft_unquotes(&data->token[i]);
		//debug
		printf("%s\n", input[i]);
		printf("token idx: %d \n", data->token[i].idx);
		print_redir_argv(data->token[i].redir);
		print_cmd_argv(data->token[i].cmd);
		//debug
		// //check_expand(&data->token[i]);
		i++;
	}
	ft_free_arr(input);
	if (data->token != NULL)
	{
		here_doc(data);
	}
	// debug
	// printf("here_doc in token[%d]\n", data->hd);
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
	// data->token = ft_calloc(data->cmd_count, sizeof(t_token));
	// if (!data->token)
	// 	return (0);
// 	i = 0;
// 	while (input[i])
// 		data->token[i] = assign_token(input[i++], i);
// 	ft_free_arr(input);
// 	data->hd = check_heredoc(data);
// 	// now iterates through the token and check redir for here_doc
// 	return (1);
// }

