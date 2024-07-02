
#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*substr;

	if (!s)
		return (NULL);
	if (len > ft_strlen((char *)s) - start)
		len = (ft_strlen((char *)s) - start);
	if (start >= ft_strlen((char *)s))
		len = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

void	*ft_safe_malloc(size_t size)
{
	void *mem_alloc;

	mem_alloc = malloc(size);
	if (!mem_alloc)
		// error_msg("Malloc Fails");
	return (mem_alloc);
}

char	*ft_safe_substr(const char *s, unsigned int start, size_t len)
{
	char *str;

	str = ft_substr(s, start, len);
	if (!str)
		// error_msg("substr failed");
	return (str);
}

char *ft_removequotes(char *str)
{
    int len;
    char *new;

    len = ft_strlen(str);
    new = ft_safe_malloc(sizeof(char) * len - 1);
    new = ft_safe_substr(str, 1, len - 2);
    return (new);
}

// void    ft_removequotes(char *str)
// {
//     int end;

//     end = ft_strlen(str) - 1;
//     printf("char 0: %c\n", str[0]);
//     printf("char end: %c\n", str[end]);
//     str[0] = 31;
//     str[end] = 31;
// }
/*
now loops through the array of strings and check the first idx, if that's a quote, we remove that and remove the last one. We can replace it with 31?
*/
// void    ft_unqotes()
// {
//     /*
//         take in each token, loop through each redir/cmd and check if the [0] is a quote then we remove them.
//     */
//     int i;

//     i = 0;
//     while (i < token->redir_len)
//     {
//         if (ft_isquote(token->redir[i][0][0]))
//             //ft_removequotes();
//         if (ft_isquote(token->redir[i][1][0]))
//             //ft_removequotes();
//         i++;
//     }
//     i = 0;
//     while (i < token->cmd_len)
//     {
//         if (ft_isquote(token->cmd[i][0]))
//             //ft_removequotes();
//         i++;
//     }
// }

int main()
{
    char *str = "\"happy 'wrold' tree\"";

    printf("here\n");
    str = ft_removequotes(str);
    printf("%s\n", str);
    return (0);
}