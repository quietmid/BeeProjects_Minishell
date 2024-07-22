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

		// //debug
		// printf("%s\n", input[i]);
		// printf("token idx: %d \n", data->token[i].idx);
		// print_redir_argv(data->token[i].redir);
		// print_cmd_argv(data->token[i].cmd);
		// //debug
// debug
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