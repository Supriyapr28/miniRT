#include "../libft/libft.h"
#include"parse.h"

static int get_expected_token_count(char *type)
{
    if (ft_strncmp(type, "A", 2) == 0)
        return (3);
    if (ft_strncmp(type, "C", 2) == 0)
        return (4);
    if (ft_strncmp(type, "L", 2) == 0)
        return (4);
    if (ft_strncmp(type, "sp", 3) == 0)
        return (4);
    if (ft_strncmp(type, "pl", 3) == 0)
        return (4);
    if (ft_strncmp(type, "cy", 3) == 0)
        return (6);
    return (0);
}

static int count_tokens(char **tokens)
{
    int count;

    count = 0;
    while (tokens[count])
        count++;
    return (count);
}

char **create_tokens(char *line)
{
    char **tokens;
    tokens = ft_split(line, ' '); 
    free(line);
    if (!tokens)
        parse_error("Memory allocation failed during tokenization");
    return (tokens);
}

int validate_token(char **tokens)
{
    int expected_count;
    int actual_count;

    if (!tokens || !tokens[0])
       return (parse_error("Invalid tokenized line"), 0);
    expected_count = get_expected_token_count(tokens[0]);
    if (expected_count == 0)
        return (parse_error("Unknown object type"), 0);
    actual_count = count_tokens(tokens);
    if (actual_count != expected_count)
        return (parse_error("Invalid token count for object"), 0);
    return (1);
}

