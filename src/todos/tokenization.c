#include "../inc/libs.h"

/* 
 * essa funcao esta modificando o input
 * o input sendo "ls -l" 
 * quando passa por ela passa a ser "ls"
*/
char *ft_gettoken(char *input, int delim, bool fst)
{
	static char *static_str = NULL;
	char *token;
	char quote = '\0';

	if (static_str == NULL && fst)
		static_str = input;
	if (static_str == NULL)
		return (NULL);
	while (*static_str && *static_str == delim)
		static_str++;
	if (*static_str == '\0')
		return (NULL);
	token = static_str;
	while (*static_str && (*static_str != delim || quote != '\0'))
	{
		if (*static_str == '\'' || *static_str == '\"')
		{
			if (quote == '\0')
				quote = *static_str;
			else if (quote == *static_str)
				quote = '\0';
		}
		static_str++;
	}
	if (*static_str)
	{
		*static_str = '\0';
		static_str++;
	}
	else
		static_str = NULL;
	printf("token para guardar: %s\t%p\n", token, &token);
	return (ft_strdup(token));
}

t_tokens	*ft_tokenlast(t_tokens *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*curr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_tokenlast(*lst);
	curr->next = new;
	new->prev = curr;
}

/* nessa versao nao precisa da funcao ft_addtoken */
void	ft_tokenization(t_shell *data)
{
    char *input;
    char *token;
    t_tokens *node; // temp para armazenar o token atual
    t_tokens *head; // cabeca da lista

    input = data->input;
    token = ft_gettoken(input, ' ', true);
    head = NULL;
    node = NULL;
	while (token != NULL)
    {
        node = ft_calloc(1, sizeof(t_tokens));
        node->content = token;
        /* abaixo so inicializo os valores */
        node->type = -1;
        node->single_qoutes = false;
        node->double_quotes = false;
        ft_tokenadd_back(&head, node); // adiciona o token atual ao fim da lista
        token = ft_gettoken(input, ' ', false);
    }
    data->tokens = head; // ponteiro tokens recebe a cabeca da lista
}
