
#include "minishell.h"

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(count, size);
	if (!alloc)
		error_msg("Calloc fails");
	return (alloc);
}

void	*ft_safe_malloc(size_t size)
{
	void *mem_alloc;

	mem_alloc = malloc(size);
	if (!mem_alloc)
		error_msg("Malloc Fails");
	return (mem_alloc);
}

char	*ft_safe_substr(const char *s, unsigned int start, size_t len)
{
	char *str;

	str = ft_substr(s, start, len);
	if (!str)
		error_msg("substr failed");
	return (str);
}
