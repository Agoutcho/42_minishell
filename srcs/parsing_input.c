/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:09:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/02/18 01:09:21 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_type(t_command *command, unsigned long i_cmd, long *i, long *k)
{
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

	add_type(command, i_cmd, i, k);
	if (command->quote == e_no_quote)
		move_space(command->input, i);
	arg_size = count_arg_size(command, command->input, *i);
	command->cmd_array[i_cmd].redir_array[*k].file_name = add_command(command, \
	command->input, i, arg_size);
	GREEN
	DEBUG("command->cmd_array[%ld].redir_array[%ld].file_name : %s", i_cmd, *k, command->cmd_array[i_cmd].redir_array[*k].file_name)
	RESET
	(*k)++;
}

int	is_dollar_ok(char *str, long *i, int change_i)
{
	if ((str[*i] == '$' && str[(*i) + 1] != '-' && str[(*i) + 1] != '?' \
		&& !ft_isalnum(str[(*i) + 1])) || !str[(*i) + 1] \
		|| str[(*i) + 1] == ' ')
	{
		if (change_i)
			(*i)++;
		return (0);
	}
	return (1);
}

int	find_lenght_in_env(t_command *command, char *str)
{
	t_env	*temp;

	temp = command->env->first;
	if (!*str)
		return (0);
	while (temp)
	{
		if (ft_strncmp(temp->key, str, ft_strlen(str) + 1) == 0)
				return (ft_strlen(temp->value));
		temp = temp->next;
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
	else
	{
		temp = ft_strdup("OLDPWD=");
		result = find_lenght_in_env(command, temp);
	}
	free(temp);
	return (result);
}

// TODO check for  $- $$ $?  $"" $ if i+1 != alphanum && ? && -
int	count_dollar_size(t_command *command, char *str, long *i, int *counter)
{
	int		size_dollar;
	int		temp_i;
	char	*temp;

	
	if (!is_dollar_ok(str, i, 1))
		return (1);
	(*i)++;
	temp_i = *i;
	if (str[*i] == '-' || str[*i] == '?')
		return (count_dollar_special(command, str, i));
	while (str[temp_i] && ft_isalnum(str[temp_i]))
		temp_i++;
	size_dollar = temp_i - *i + 1;
	temp = (char *)malloc(sizeof(char) * (size_dollar + 1));
	if (!temp)
		big_free(command);
	temp[size_dollar] = 0;
	temp[--size_dollar] = '=';
	while (size_dollar-- > 0)
		temp[size_dollar] = str[(*i) + size_dollar];
	*counter = (*counter) + find_lenght_in_env(command, temp);
	(*i) += temp_i - *i;
	free(temp);
	return (0);
}

int	count_tilde_size(t_command *command, char *str, long *i)
{
	int		ret_value;
	int		temp_i;

	(*i)++;
	temp_i = *i;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	if (str[temp_i] == '+')
		ret_value = find_lenght_in_env(command, "PWD=");
	else if (str[temp_i] == '-')
		ret_value = find_lenght_in_env(command, "OLDPWD=");
	else
		ret_value = find_lenght_in_env(command, "HOME=");
	if (ret_value == 0 && (str[temp_i] == '-' || str[temp_i] == '+'))
		ret_value = 2;
	else if (ret_value == 0)
		ret_value = 1;
	return (ret_value);
}

int	is_stop_char(t_command *command, char c)
{
	if (command->quote != e_no_quote)
		return (0);
	else if (command->quote == e_no_quote && !is_redir(c) && c != '|' \
			&& c != ' ' && c != '\t' && c != '\n' && c != '\r' && c)
		return (0);
	return (1);
}

// check_special => '~' // TODO check ~/ ~+ ~-
int	is_tilde_ok(char *str, long i)
{
	if (str[i] != '~')
		return (0);
	i++;
	if ((i == 1 || str[i - 2] == ' ') && (!str[i] || str[i] == ' ' || str[i] == '/' \
		|| str[i] == ':' || str[i] == '+' || str[i] == '-' || str[i] == '<' \
		|| str[i] == '>' || str[i] == '|'))
	{
		if((str[i] == '+' || str[i] == '-') && (str[i + 1] && str[i + 1] != ' ' \
		&& str[i + 1] != '/' && str[i + 1] != ':' && str[i + 1] != '<' \
		&& str[i + 1] != '>' && str[i + 1] != '|'))
			return (0);
		return (1);
	}
	return (0);
}

int	count_arg_size(t_command *command, char *str, long i)
{
	int	counter;

	counter = 0;
	if (command->quote != e_no_quote && str[i] == (char)command->quote)
		command->quote = e_no_quote;
	// check_special => '~' // TODO check ~/ ~+ ~-
	while (str[i] && !is_stop_char(command, str[i]))
	{
		set_quote(command, &i, 1);
		if (str[i] && str[i] == '$' && command->quote != e_little_quote)
			counter += count_dollar_size(command, str, &i, &counter); // check $- $$ $?  $"" $
		else if (str[i] && command->quote == e_no_quote && is_tilde_ok(str, i))
			counter += count_tilde_size(command, str, &i);
		else if (str[i] && command->quote != e_no_quote && str[i] != (char)command->quote)
		{
			i++;
			counter++;
		}
		else if (str[i] && command->quote == e_no_quote && !is_stop_char(command, str[i]) \
				&& str[i] != '\'' && str[i] != '"')
		{
			i++;
			counter++;
		}
	}
	return (counter);
}

t_args	*add_args(t_command *command, long *i, unsigned long i_cmd, int size)
{
	t_args	*temp;
	int	arg_size;
	(void)size;
	arg_size = count_arg_size(command, command->input, *i);
	temp = (t_args *)malloc(sizeof(t_args));
	if (!temp)
		big_free(command);
	temp->next = NULL;
	temp->arg = add_command(command, command->input, i, arg_size);
	if (command->cmd_array[i_cmd].args)
	{
		temp->first = command->cmd_array[i_cmd].args->first;
		command->cmd_array[i_cmd].args->next = temp;
	}
	else
		temp->first = temp;
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
		if (ft_strncmp(temp->key, t_key, ft_strlen(t_key) + 1) == 0)
		{
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

		temp_i = *i;
	while (str[temp_i] && ft_isalnum(str[temp_i]))
		temp_i++;
	size_dollar = temp_i - *i + 1;
		temp_key = (char *)malloc(sizeof(char) * (size_dollar + 1));
	if (!temp_key)
		big_free(command);
	temp_key[size_dollar] = 0;
	temp_key[--size_dollar] = '=';
	while (size_dollar-- > 0)
		temp_key[size_dollar] = str[(*i) + size_dollar];
	find_val_in_env(command, temp_key, parsed, index);
	(*i) += temp_i - *i;
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
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
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

int	add_tilde_home(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first; 
	temp = ft_strdup("HOME=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
				parsed[*index] = tenv->value[i_val];
				(*index)++;
				i_val++;
			}
			i_val = 1;
			break ;
		}
		tenv = tenv->next;
	}
	(*i)++;
	free(temp);
	return (i_val);
}

int	add_tilde_plus(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first; 
	temp = ft_strdup("PWD=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
				parsed[*index] = tenv->value[i_val];
				(*index)++;
				i_val++;
			}
			i_val = 1;
			break ;
		}
		tenv = tenv->next;
	}
	(*i) = (*i) + 2;
	free(temp);
	return (i_val);
}

int	add_tilde_hyphen(t_command *command, long *i, char *parsed, long *index)
{
	char	*temp;
	int		i_val;
	t_env	*tenv;

	i_val = 0;
	tenv = command->env->first; 
	temp = ft_strdup("OLDPWD=");
	if (!temp)
		big_free(command);
	while (tenv)
	{
		if (ft_strncmp(tenv->key, temp, ft_strlen(temp) + 1) == 0)
		{
			while (tenv->value[i_val])
			{
				parsed[*index] = tenv->value[i_val];
				(*index)++;
				i_val++;
			}
			i_val = 1;
			break ;
		}
		tenv = tenv->next;
	}
	(*i) = (*i) + 2;
	free(temp);
	return (i_val);
}

void	add_tilde(t_command *command, char *str, long *i, char *temp, long *i_temp)
{
	int		ret_value;
	int		temp_i;
	
	temp_i = *i;
	temp_i++;
	if (str[temp_i] == '-' || str[temp_i] == '+')
		temp_i++;
	if (str[temp_i - 1] == '+')
		ret_value = add_tilde_plus(command, i, temp, i_temp);
	else if (str[temp_i - 1] == '-')
		ret_value = add_tilde_hyphen(command, i, temp, i_temp);
	else
		ret_value = add_tilde_home(command, i, temp, i_temp);
	if (ret_value == 0 && (str[temp_i - 1] == '-' || str[temp_i - 1] == '+'))
	{
		temp[*i_temp] = str[temp_i - 2];
		(*i_temp)++;
		temp[*i_temp] = str[temp_i - 1];
		(*i_temp)++;
		(*i) = (*i) + 2;
	}
	else if (ret_value == 0)
	{
		temp[*i_temp] = str[temp_i - 1];
		(*i_temp)++;
		(*i)++;
	}
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
	while (temp)
	{
		if (ft_strncmp(temp->key, t_key, ft_strlen(t_key) + 1) == 0)
		{
			while (temp->value[i])
			{
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

// TODO check $- $$ $?  $"" $
char	*add_command(t_command *command, char *str, long *i, int size)
{
	char *temp;
	long index;

	index = 0;
	temp = (char *)malloc(sizeof(char) * size + 1);
	if (!temp)
		big_free(command);
	if (command->quote != e_no_quote && str[*i] == (char)command->quote)
		command->quote = e_no_quote;
	while (str[*i] && !is_stop_char(command, str[*i]))
	{
		set_quote(command, i, 1);
		if (str[*i] && str[*i] == '$' && command->quote != e_little_quote)
			add_dollar(command, str, i, temp, &index); 
		else if (str[*i] && command->quote == e_no_quote && is_tilde_ok(str, *i))
			add_tilde(command, str, i, temp, &index);
		else if (str[*i] && command->quote != e_no_quote && str[*i] != (char)command->quote)
		{
			while (str[*i] != (char)command->quote && is_dollar_quoted(command->quote, str[*i]))
			{
				temp[index] = str[*i];
				index++;
				(*i)++;
			}
		}
		else if (str[*i] && command->quote == e_no_quote && !is_stop_char(command, str[*i]) \
				&& str[*i] != '\'' && str[*i] != '"')
		{
			temp[index] = str[*i];
			index++;
			(*i)++;
		}
	}
	temp[index] = 0;
	return (temp);
}

void	do_command(t_command *command, unsigned long i_cmd, long *i)
{
	int	arg_size;

	arg_size = count_arg_size(command, command->input, *i);
	if (command->cmd_array[i_cmd].is_cmd_filled == 0)
	{
		command->cmd_array[i_cmd].is_cmd_filled = 1;
		command->cmd_array[i_cmd].the_cmd = add_command(command, \
				command->input, i, arg_size);
		RED
		DEBUG("command->cmd_array[%ld].the_cmd : %s", i_cmd, command->cmd_array[i_cmd].the_cmd)
		RESET
	}
	else
	{
		command->cmd_array[i_cmd].args = add_args(command, i, i_cmd, arg_size);
		YELLOW
		DEBUG("command->cmd_array[%ld].args : %s", i_cmd, command->cmd_array[i_cmd].args->arg)
		RESET
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
	command->quote = e_no_quote;
	command->cmd_array[0].args = NULL;
	while (j < command->size_cmd_array && command->input[i])
	{
		if (command->quote == e_no_quote)
			move_space(command->input, &i);
		set_quote(command, &i, 0);
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
