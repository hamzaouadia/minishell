#include "minishell.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	//leaks_removal(&g_global.g, new_node);
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_heredoc	*ft_lstnew_heredoc(int data)
{
	t_heredoc	*new_node;

	new_node = malloc(sizeof(t_heredoc));
	//leaks_removal(&g_global.g, new_node);
	if (!new_node)
		return (NULL);
	new_node->fd_pipe_heredoc = data;
	new_node->next = NULL;
	return (new_node);
}
