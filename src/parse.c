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

static char	***redir_argv(char *str, int len, char ***redir)
{
	int		i;
	int		x;
	char	q;

	i = 0;
	x = 0;
	len = 0;
	q = 0;
	while (str[i])
	{
		if (ft_isredir(str[i]) && !(quote_finder(str[i], q)))
		{
			i = extract_redir(str, redir[len], i);
			i = skip_whitespace(str, i);
			x = i;
			i = skip_whitespace2(str, i);
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

static char	**cmd_argv(char **temp, int len)
{
	char	**cmd;
	int		i;
	int		j;

	cmd = (char **)ft_safe_calloc((len + 1), sizeof(char *));
	i = 0;
	j = 0;
	while (temp[i])
	{
		if (ft_isredir(temp[i][0]))
			i = extract_cmd(temp, i);
		else if (i > 0 && ((!(ft_isredir(temp[i - 1][0])) && temp[i])
			|| (!ft_isredir(temp[i - 1][ft_strlen(temp[i - 1])]))))
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

static void	assign_token(t_token *t)
{
	char	**temp;
	char	*str;

	str = t->cmd_line;
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
		t->cmd = NULL;
}

static t_token	init_token(char *str, int i)
{
	t_token	t;
	int		x;

	t.hd = 0;
	t.idx = i;
	t.cmd_len = 0;
	t.cmd_line = ft_strdup(str);
	t.redir_len = calcu_redir(str);
	if (t.redir_len > 0)
		t.redir = (char ***)ft_safe_malloc((t.redir_len + 1) * sizeof(char **));
	x = -1;
	while (++x < t.redir_len)
		t.redir[x] = (char **)ft_safe_calloc(3, sizeof(char *));
	if (t.redir_len == 0)
		t.redir = NULL;
	free(str);
	return (t);
}

// static void print_redir_argv(char ***redir)
// {
// 	int i;
// 	i = 0;
// 	if (!redir)
// 		return ;
// 	while (redir[i])
// 	{
// 		printf("redir [%d] \n", i);
//         printf("redir dir: %s\n", redir[i][0]);
//         printf("redir fd: %s\n", redir[i][1]);
// 		i++;
//     }
// }

// // 		//debug
// // 		printf("%s\n", input[i]);
// // 		printf("token idx: %d \n", data->token[i].idx);
// // 		print_redir_argv(data->token[i].redir);
// // 		print_cmd_argv(data->token[i].cmd);
// // 		//debug
// // debug

// static void print_cmd_argv(char **redir)
// {
// 	int i;
// 	if (!redir)
// 		return ;
//     for (i = 0; redir[i] != NULL; i++)
//     {
//         printf("cmd: %s\n", redir[i]);
//     }
// }

int	parse_start(t_data *data, char *line)
{
	// char *exp_line;
	char	**tmp;
	int		i;

	i = 0;
	data->cmd_count = pipe_scans(line);
	data->token = malloc(sizeof(t_token) * data->cmd_count);
	if (!data->token)
		return (0);
	tmp = ft_split(line, 31);
	while (tmp[i])
	{
		data->token[i] = init_token(tmp[i], i);
		data->token[i].cmd_line = check_expand(data->token[i].cmd_line, data);
		assign_token(&data->token[i]);
		data->hd += check_heredoc(&data->token[i]);
		ft_unquotes(&data->token[i]);
		i++;
	}
	while (tmp[i])
		free(tmp[i--]);
	free (tmp);
	if (data->token != NULL)
	{
		if (!here_doc(data))
			return (0);
		if (data->cmd_count == 1 && data->token[0].cmd == NULL)
			return (0);
	}
	return (1);
}

// // debug


