/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/16 04:43:28 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_type(t_command *command, unsigned long i_cmd, long *i, long *k)
{
	// DEBUG()

	if (command->input[*i] == '>' && command->input[(*i) + 1] == '>')
		command->cmd_array[i_cmd].redir_array[*k].type = e_append;
	else if (command->input[*i] == '>' && command->input[(*i) + 1] != '>')
		command->cmd_array[i_cmd].redir_array[*k].type = e_out;
	else if (command->input[*i] == '<' && command->input[(*i) + 1] == '<')
		command->cmd_array[i_cmd].redir_array[*k].type = e_heredoc;
	else if (command->input[*i] == '<' && command->input[(*i) + 1] != '<')
		command->cmd_array[i_cmd].redir_array[*k].type = e_in;
	GREEN
		DEBUG("type : %d", command->cmd_array[i_cmd].redir_array[*k].type)
		RESET
		if (command->cmd_array[i_cmd].redir_array[*k].type == e_append \
				|| command->cmd_array[i_cmd].redir_array[*k].type == e_heredoc)
			(*i) = (*i) + 2;
		else 
			(*i)++;
}

void	do_redirection(t_command *command, unsigned long i_cmd, long *i, long *k)
{
	int	arg_size;

	DEBUG();
	add_type(command, i_cmd, i, k);
	// DEBUG()
	if (command->quote == e_no_quote)
		move_space(command->input, i);
	arg_size = count_arg_size(command, command->input, *i);
	DEBUG("arg_size : %d", arg_size)
		command->cmd_array[i_cmd].redir_array[*k].file_name = add_command(command, \
		command->input, i, arg_size);
	GREEN
	DEBUG("command->cmd_array[%ld].redir_array[%ld].file_name : %s", i_cmd, *k, command->cmd_array[i_cmd].redir_array[*k].file_name)
	RESET
	// DEBUG("k : %ld", *k);
	DEBUG("redir : %s", command->cmd_array[i_cmd].redir_array[*k].file_name);
	(*k)++;
}

int	is_dollar_ok(char *str, long *i, int change_i)
{
	GREEN
	DEBUG("str[%ld] : %c", *i, str[*i])
	if ((str[*i] == '$' && str[(*i) + 1] != '-' && str[(*i) + 1] != '?' \
		&& !ft_isalnum(str[(*i) + 1])) || !str[(*i) + 1] \
		|| str[(*i) + 1] == ' ')
	{
		DEBUG("dollar pas bon")
		DEBUG("str[%ld] : %c", *i, str[*i])
		DEBUG("str[%ld] : %c", (*i) + 1, str[(*i) + 1])
		if (change_i)
			(*i)++;
		return (0);
	}
	return (1);
	RESET
}

int	find_lenght_in_env(t_command *command, char *str)
{
	t_env	*temp;

	DEBUG("str : %p", str);
	DEBUG("str : %s", str);
	DEBUG("command->env : %p", command->env);
	DEBUG("command->env->first : %p", command->env->first);
	temp = command->env->first;
	DEBUG("temp : %p", temp);
	if (!*str)
		return (0);
	while (temp)
	{
		// DEBUG("key : %s", temp->key);
		// DEBUG("temp->first : %p", temp->first);
		// DEBUG("command->env : %p", command->env);
		// DEBUG("command->env->first : %p", command->env->first);
		if (ft_strncmp(temp->key, str, ft_strlen(str) + 1) == 0)
		{
			// DEBUG("key : %s", temp->key);
			// DEBUG("value : %s", temp->value)
			// 	DEBUG("len : %zu", ft_strlen(temp->value))
				return (ft_strlen(temp->value));
		}
		temp = temp->next;
		// DEBUG("command->env : %p", command->env);
		// DEBUG("command->env->first : %p", command->env->first);
	}
	return (0);
}

int	count_dollar_special(t_command *command, char *str, long *i)
{
	char	*temp;
	int	result;

	if (str[*i] == '?')
	{
		(*i)++;
		temp = ft_itoa(g_exit_code);
		result = (int)ft_strlen(temp);
	}
	else // if (str[*i] == '-')
	{
		temp = ft_strdup("OLDPWD=");
		result = find_lenght_in_env(command, temp);
	}
	free(temp);
	return (result);
}

int	count_dollar_size(t_command *command, char *str, long *i, int *counter)
{
	int		size_dollar;
	int		temp_i;
	char	*temp;

	// check for  $- $$ $?  $"" $ if i+1 != alphanum && ? && -
	DEBUG("*i : %ld", *i)
		if (!is_dollar_ok(str, i, 1))
			return (1);
	(*i)++;
	// DEBUG("*i : %ld", *i)
	temp_i = *i;
	if (str[*i] == '-' || str[*i] == '?')
		return (count_dollar_special(command, str, i));
	while (str[temp_i] && ft_isalnum(str[temp_i]))
		temp_i++;
	size_dollar = temp_i - *i + 1;
	// DEBUG("size_dollar : %d", size_dollar)
	temp = (char *)malloc(sizeof(char) * (size_dollar + 1));
	if (!temp)
		big_free(command);
	temp[size_dollar] = 0;
	temp[--size_dollar] = '=';
	while (size_dollar-- > 0)
	{
		temp[size_dollar] = str[(*i) + size_dollar];
		// DEBUG("temp[size_dollar] : %c str[(*i) + size_dollar] : %c", temp[size_dollar], str[(*i) + size_dollar])
	}
	// DEBUG("size_dollar : %d", size_dollar)
	*counter = (*counter) + find_lenght_in_env(command, temp);
	(*i) += temp_i - *i;
	// DEBUG("*i : %ld", *i);
	free(temp);
	return (0);
}

int	is_stop_char(t_command *command, char c)
{
	// DEBUG("c : %c", c);
	if (command->quote != e_no_quote)
	{
		// DEBUG("c : %d, quote : %d", c, command->quote);
		return (0);
	}
	else if (command->quote == e_no_quote && !is_redir(c) && c != '|' \
			&& c != ' ' && c != '\t' && c != '\n' && c != '\r' && c)
	{
		// DEBUG("c : %d", c);
		return (0);
	}
	return (1);
}

int	is_tilde_ok(t_command *command, char *str, int *counter, long i)
{
	int 	ret_value;

	PURPLE
	if (str[i - 1])
		DEBUG("str[%ld] : %c", i - 1, str[i - 1])
	DEBUG("str[%ld] : %c", i, str[i])
	if (str[i + 1])
		DEBUG("str[%ld] : %c", i + 1, str[i + 1])
	i++;
	if (str[i - 1] != '~' || (str[i] && str[i] != ' ' && str[i] != '/' \
		&& str[i] != ':' && str[i] != '+' && str[i] != '-' && str[i] != '<' \
		&& str[i] != '>' && str[i] != '|'))
		return (0);
	DEBUG("str[%ld] : %c", i, str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i - 1] == '+' && (!str[i] || str[i] == ' ' \
		|| str[i] == '/' || str[i] == ':' || str[i] == '<' \
		|| str[i] == '>' || str[i] == '|'))
		ret_value = find_lenght_in_env(command, "PWD=");
	if (str[i - 1] == '-' && (!str[i] || str[i] == ' ' \
		|| str[i] == '/' || str[i] == ':' || str[i] == '<' \
		|| str[i] == '>' || str[i] == '|'))
		ret_value = find_lenght_in_env(command, "OLDPWD=");
	if (!str[i] || str[i] == ' ' || str[i] == '/' || str[i] == ':')
		ret_value = find_lenght_in_env(command, "HOME=");
	DEBUG("str[%ld] : %c", i, str[i]);
	if (str[i] == '/' || str[i] == ':')
		ret_value += count_arg_size(command, command->input, i);
	*counter = *counter + ret_value;
	DEBUG("counter : %d", *counter);
	return (ret_value);
}

int	count_arg_size(t_command *command, char *str, long i)
{
	int	counter;

	DEBUG();
	counter = 0;
	if (command->quote != e_no_quote && str[i] == (char)command->quote)
		command->quote = e_no_quote;
	// check_special => '~' // TODO check ~/ ~+ ~-
	if (command->quote == e_no_quote && is_tilde_ok(command, str, &counter, i))
		return (counter);
	while (str[i] && !is_stop_char(command, str[i]))
	{
		// RED
		// DEBUG("str[%ld] : %c", i, str[i]);
		// DEBUG("quote : %d", command->quote)
		set_quote(command, &i, 1);
		// DEBUG("quote : %d", command->quote)
		// DEBUG("str[%ld] : %c", i, str[i]);
		if (str[i] && str[i] == '$' && command->quote != e_little_quote)
			counter += count_dollar_size(command, str, &i, &counter); // check $- $$ $?  $"" $
		else if (command->quote == e_no_quote && is_tilde_ok(command, str, &counter, i))
			return (counter);
		else if (str[i] && command->quote != e_no_quote && str[i] != (char)command->quote)
		{
			// DEBUG("str[%ld] : %c", i, str[i]);
			i++;
			counter++;
		}
		else if (str[i] && command->quote == e_no_quote && !is_stop_char(command, str[i]) \
				&& str[i] != '\'' && str[i] != '"')
		{
			// DEBUG("str[%ld] : %c", i, str[i]);
			i++;
			counter++;
		}
		// DEBUG("counter : %d", counter)
	}
	// DEBUG("counter : %d", counter)
	// RESET
	return (counter);
}

t_args	*add_args(t_command *command, long *i, unsigned long i_cmd, int size)
{
	t_args	*temp;
	int	arg_size;
	(void)size;

	arg_size = count_arg_size(command, command->input, *i);
	YELLOW
		DEBUG("arg_size : %d", arg_size)
		// DEBUG("sizeof(t_args) : %ld", sizeof(t_args))
		temp = (t_args *)malloc(sizeof(t_args));
	if (!temp)
		big_free(command);
	temp->next = NULL;
	temp->arg = add_command(command, command->input, i, arg_size);
	DEBUG("arg : %s", temp->arg);
	if (command->cmd_array[i_cmd].args)
	{
		// DEBUG("TEST")
		temp->first = command->cmd_array[i_cmd].args->first;
		command->cmd_array[i_cmd].args->next = temp;
	}
	else
		temp->first = temp;
	RESET
		return (temp);
}

void	find_val_in_env(t_command *command, char *t_key, char *parsed, long *idex)
{
	t_env	*temp;
	int	i;

	i = 0;
	temp = command->env->first;
	while (temp)
	{
		// DEBUG("key : %s", temp->key);
		if (ft_strncmp(temp->key, t_key, ft_strlen(t_key) + 1) == 0)
		{
			DEBUG("key : %s", temp->key);
			DEBUG("value : %s", temp->value)
				DEBUG("len : %zu", ft_strlen(temp->value))
				while (temp->value[i])
				{
					parsed[*idex] = temp->value[i];
					(*idex)++;
					i++;
				}
			return ;
		}
		temp = temp->next;
	}
}

void	adding_dollar_env(t_command *command, char *str, long *i, char *parsed, long *index)
{
	int	size_dollar;
	int	temp_i;
	char	*temp_key;

	DEBUG("*i : %ld", *i)
		temp_i = *i;
	while (str[temp_i] && ft_isalnum(str[temp_i]))
		temp_i++;
	size_dollar = temp_i - *i + 1;
	DEBUG("size_dollar : %d", size_dollar)
		temp_key = (char *)malloc(sizeof(char) * (size_dollar + 1));
	if (!temp_key)
		big_free(command);
	temp_key[size_dollar] = 0;
	temp_key[--size_dollar] = '=';
	while (size_dollar-- > 0)
	{
		temp_key[size_dollar] = str[(*i) + size_dollar];
		// DEBUG("temp_key[size_dollar] : %c str[(*i) + size_dollar] : %c", temp_key[size_dollar], str[(*i) + size_dollar])
	}
	// DEBUG("size_dollar : %d", size_dollar)
	find_val_in_env(command, temp_key, parsed, index);
	(*i) += temp_i - *i;
	DEBUG("*i : %ld", *i);
	DEBUG("str[%ld] : %c", *i, str[*i]);
	free(temp_key);
}

void	adding_qmark(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int	i_val;

	i_val = 0;
	temp = ft_itoa(g_exit_code);
	if (!temp)
		big_free(command);
	while (temp[i_val])
	{
		parsed[*index] = temp[i_val];
		(*index)++;
		i_val++;
	}
	(*i)++;
	free(temp);
}

void	adding_hyphen(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int	i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first; 
	temp = ft_strdup("OLDPWD=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		DEBUG("key : %s", tenv->key);
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			DEBUG("value : %s", tenv->value)
				DEBUG("len : %zu", ft_strlen(tenv->value))
				while (tenv->value[i_val])
				{
					DEBUG("tenv->value[i_val] : %c", tenv->value[i_val])
						parsed[*index] = tenv->value[i_val];
					(*index)++;
					i_val++;
				}
			break ;
		}
		tenv = tenv->next;
	}
	(*i)++;
	free(temp);
}

// check $- $$ $?  $"" $
// TODO peut etre ajouter '$_' => la derniere variable connue  https://abs.traduc.org/abs-5.3-fr/ch09.html
void	add_dollar(t_command *command, char *str, long *i, char *temp, long *index)
{
	GREEN
		DEBUG()
		RESET
		if (command->quote == e_no_quote \
				&& (str[(*i) + 1] == '\'' || str[(*i) + 1] == '"'))
		{
			(*i)++;
			return ;
		}
		else if (!is_dollar_ok(str, i, 0))
		{
			temp[*index] = str[*i];
			(*index)++;
			(*i)++;
			return ;
		}
	(*i)++;
	if (str[*i] == '-')
		adding_hyphen(command, i, temp, index);
	else if (str[*i] == '?')
		adding_qmark(command, i, temp, index);
	else
		adding_dollar_env(command, str, i, temp, index);
}

int	is_dollar_quoted(t_quote quote, char c)
{
	if (quote == e_big_quote && c == '$')
		return (0);
	return (1);
}

int	find_til_in_env(t_command *command, char *t_key, char *parsed, long *idex)
{
	t_env	*temp;
	int	i;

	i = 0;
	temp = command->env->first;
	DEBUG("t_key : %s", t_key);
	while (temp)
	{
		// DEBUG("key : %s", temp->key);
		if (ft_strncmp(temp->key, t_key, ft_strlen(t_key) + 1) == 0)
		{
			DEBUG("key : %s", temp->key);
			DEBUG("value : %s", temp->value)
				DEBUG("len : %zu", ft_strlen(temp->value))
				while (temp->value[i])
				{
					// DEBUG("temp->value[%d] : %c", i, temp->value[i])
					parsed[*idex] = temp->value[i];
					(*idex)++;
					i++;
				}
				parsed[*idex] = 0;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	add_tild(t_command *command, char *str, long *i, char **parsed, long arg_size)
{
	char	*new_com;
	char	*join;
	int		ret_value;
	long	index;

	index = 0;
	ret_value = 0;
	PURPLE
	if (str[*i - 1])
		DEBUG("str[%ld] : %c", *i - 1, str[*i - 1])
	DEBUG("str[%ld] : %c", *i, str[*i])
	if (str[*i + 1])
		DEBUG("str[%ld] : %c", *i + 1, str[*i + 1])
	if (str[*i] != '~' || (str[*i + 1] && str[*i + 1] != ' ' && str[*i + 1] != '/' \
		&& str[*i + 1] != ':' && str[*i + 1] != '+' && str[*i + 1] != '-' && str[*i + 1] != '<' \
		&& str[*i + 1] != '>' && str[*i + 1] != '|'))
		return (ret_value);
	(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	DEBUG("str[%ld] : %c", *i, str[*i])
	if (str[*i - 1] == '+' && (!str[*i] || str[*i] == ' ' \
		|| str[*i] == '/' || str[*i] == ':' || str[*i] == '<' \
		|| str[*i] == '>' || str[*i] == '|'))
		ret_value = find_til_in_env(command, "PWD=", *parsed, &index);
	if (str[*i - 1] == '-' && (!str[*i] || str[*i] == ' ' \
		|| str[*i] == '/' || str[*i] == ':' || str[*i] == '<' \
		|| str[*i] == '>' || str[*i] == '|'))
		ret_value = find_til_in_env(command, "OLDPWD=", *parsed, &index);
	if (!str[*i] || str[*i] == ' ' || str[*i] == '/' || str[*i] == ':')
		ret_value = find_til_in_env(command, "HOME=", *parsed, &index);
	if (str[*i] == '/' || str[*i] == ':')
	{
		DEBUG()
		new_com = add_command(command, command->input, i, arg_size - index);
		DEBUG("new_com : %s", new_com)
		join = ft_strjoin(*parsed, new_com);
		DEBUG("join : %s", join)
		free (*parsed);
		DEBUG("Before parsed : %s", *parsed)
		*parsed = join;
		DEBUG("After parsed : %s", *parsed)
		free (new_com);
	}
	return (ret_value);
}

char	*add_command(t_command *command, char *str, long *i, int size)
{
	char *temp;
	long index;

	CYAN
		DEBUG();
	index = 0;
	temp = (char *)malloc(sizeof(char) * size + 1);
	if (!temp)
		big_free(command);
	if (command->quote != e_no_quote && str[*i] == (char)command->quote)
		command->quote = e_no_quote;
	if (command->quote == e_no_quote && add_tild(command, str, i, &temp, size))
		return (temp);
	while (str[*i] && !is_stop_char(command, str[*i]))
	{
		// DEBUG("str[%ld] : %c %d", *i, str[*i],str[*i]);
		set_quote(command, i, 1);
		// DEBUG("str[%ld] : %c %d", *i, str[*i],str[*i]);
		if (str[*i] && str[*i] == '$' && command->quote != e_little_quote)
			add_dollar(command, str, i, temp, &index); // check $- $$ $?  $"" $
		else if (str[*i] && command->quote != e_no_quote && str[*i] != (char)command->quote)
		{
			// DEBUG()
			// add_with_quote();
			while (str[*i] != (char)command->quote && is_dollar_quoted(command->quote, str[*i]))
			{
				// DEBUG("temp[%ld] : %c str[%ld] : %c", index, temp[index], *i, str[*i]);
				temp[index] = str[*i];
				index++;
				(*i)++;
			}
		}
		else if (str[*i] && command->quote == e_no_quote && !is_stop_char(command, str[*i]) \
				&& str[*i] != '\'' && str[*i] != '"')
		{
			DEBUG("temp[%ld] : %c str[%ld] : %c", index, temp[index], *i, str[*i]);
			temp[index] = str[*i];
			index++;
			(*i)++;
		}
	}
	temp[index] = 0;
	RESET
		return (temp);
}

// PROBLEME avec les quote a la fin "echo" donne echo"
void	do_command(t_command *command, unsigned long i_cmd, long *i)
{
	int	arg_size;

	DEBUG("input : %s", command->input);
	arg_size = count_arg_size(command, command->input, *i);
	DEBUG("arg_size : %d", arg_size)
		if (command->cmd_array[i_cmd].is_cmd_filled == 0)
		{
			// DEBUG("*i : %ld", *i);
			// DEBUG("arg_size : %d", arg_size);
			command->cmd_array[i_cmd].is_cmd_filled = 1;
			command->cmd_array[i_cmd].the_cmd = add_command(command, \
					command->input, i, arg_size);
			RED
				DEBUG("command->cmd_array[%ld].the_cmd : %s", i_cmd, command->cmd_array[i_cmd].the_cmd)
				RESET
				// DEBUG("*i : %ld", *i);
		}
		else
		{
			// BLUE
			// while (command->cmd_array[i_cmd].args && command->cmd_array[i_cmd].args->next)
			// {
			//     DEBUG("i_cmd : %ld", i_cmd)
			//     command->cmd_array[i_cmd].args = command->cmd_array[i_cmd].args->next;
			// }
			// DEBUG("arg before %p", command->cmd_array[i_cmd].args)
			command->cmd_array[i_cmd].args = add_args(command, i, i_cmd, arg_size);
			YELLOW
				DEBUG("command->cmd_array[%ld].args : %s", i_cmd, command->cmd_array[i_cmd].args->arg)
				RESET
				// BLUE
				// DEBUG("arg after  %p", command->cmd_array[i_cmd].args)
				// DEBUG("arg after  %p", command->cmd_array[i_cmd].args->next)
				// RESET
		}
}

// TODO ~ et ~/ et ~:    https://abs.traduc.org/abs-5.3-fr/ch03.html#tilde
// ~ = $HOME
// ~+ = $PWD
// ~- = $OLDPWD

// command->input est malloc 
// command->env est malloc
// command->cmd.cmd_array est malloc
// TODO add tilde management
void	parsing_input(t_command *command)
{
	long			i;
	unsigned long	j;
	long			k;

	i = 0;
	j = 0;
	k = 0;
	// PURPLE
	// DEBUG("command->cmd.size : %ld", command->size_cmd_array);
	// RESET
	command->quote = e_no_quote;
	command->cmd_array[0].args = NULL;
	while (j < command->size_cmd_array && command->input[i])
	{
		DEBUG("command->quote : %d i : %ld j : %ld", command->quote, i, j);
		// PURPLE
		// DEBUG("command->input[%ld] : %c", i, command->input[i])
		// DEBUG("command->input[%ld] : %d", i, command->input[i])
		// DEBUG("j : %ld", j)
		// RESET
		if (command->quote == e_no_quote)
			move_space(command->input, &i);
		// PURPLE
		// DEBUG("command->input[%ld] : %c", i, command->input[i])
		// DEBUG("command->input[%ld] : %d", i, command->input[i])
		// DEBUG("j : %ld", j)
		// RESET
		set_quote(command, &i, 0);
		DEBUG("command->quote : %d i : %ld j : %ld", command->quote, i, j);
		if (command->quote == e_no_quote && command->input[i] == '|')
		{
			j++;
			i++;
			k = 0;
		}
		else if (command->quote == e_no_quote && is_redir(command->input[i]))
			do_redirection(command, j, &i, &k);
		else if (command->input[i])
			do_command(command, j, &i);
	}
}
