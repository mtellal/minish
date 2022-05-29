#include "input.h"

//rends 1 si pas valide
int ft_valid_char(char c)
{
    //printf("char=%c\n", c);
    if (ft_isalnum(c) || c == '_')
        return (0);
    return (1);
}

void    ft_print_error1(char *str)
{
    write(2, "export: '", 9);
    write(2, str, ft_strlen(str));
    write(2, "': not a valid identifier\n", 26);
}

int ft_str_valid(char *str)
{
    int i;
    //int len;

    i = 0;
    //len = ft_strlen(str);
    while (str[i] != '\0' && str[i] != '=')
    {
        if (ft_valid_char(str[i]))
        {
            ft_print_error1(str);
            return (1);
        }
        i++;
    }
    if (str[i] == '\0')
        return (1);
    while (str[i] != '\0')
    {
        if (str[i] == '(')
        {
            write(2, "syntax error near unexpected token `('\n", 39);
            return (1);
        }
        else if (str[i] == ')')
        {
            write(2, "syntax error near unexpected token `)'\n", 39);
            return (1);
        }
        i++;
    }
    return (0);
}

void    ft_export(t_input *s, char *str)
{
    t_env   *new;
    t_env   *tmp;
    unsigned int len;

    if (ft_str_valid(str))
        return ;
    new = ft_env_copy(str);
    tmp = s->env;
    len = ft_strlen(new->var);
    while (tmp->next != NULL)
    {
        if (ft_strlen(tmp->var) == len && ft_memcmp(tmp->var, new->var, len) == 0)
        {
            tmp->content = new->content;
            return ;
        }
        tmp = tmp->next;
    }
    if (ft_strlen(tmp->var) == len && ft_memcmp(tmp->var, new->var, len) == 0)
    {
        tmp->content = new->content;
        return ;
    }
    ft_lstadd_back_env(&s->env, new);
}
