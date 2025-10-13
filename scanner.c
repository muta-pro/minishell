/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:07:01 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/13 17:40:41 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_token	scan_word(t_scanner *scanner)
{
	if (peek(scanner) == '$' && peek_next(scanner) == '?')
	{
		advance(scanner);
		advance(scanner);
		return (create_token(T_EXIT_STATUS, "$?"));
	}
	if (peek(scanner) == '"' || peek(scanner) == '\'')
		has_quotes = 1;
	//scan word
	if (has_quotes)
		return (create_token(T_STR, buffer));
	else
		return (create_token(T_WORD, buffer));
	if (peek(scanner) == '$')
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
		while (ft_isalnum(peek(scanner)) || peek(scanner) == '_')
		{
			append_char(scanner, peek(scanner));
			advance(scanner);
		}
		return (create_token(T_VAR, get_buff_lexeme(scanner)));
	}
	while (!is_whitespace(peek(scanner)) && !is_operator(peek(scanner))
		&& peek(scanner) != '\0' && !is_quote(peek(scanner)))
	{
		append_char(scanner, peek(scanner));
		advance(scanner);
	}
	return (create_token(T_WORD, get_buff_lexeme(scanner)));
}

static void	scan_token(const char *input_text)
{
	while (**input_text == ' ')
		(*input_text)++;
	if (**input_text == '\0')
		return (t_tok_type)
	{T_EOF, NULL};
}
static t_token operator_scan(t_scanner *scanner)
{

}
boundaries_id();
whitespace();//drops whitespace/tabs/newlines before collecting token
void invalid_tok();

t_scan_state *curr_state(char *input_text)
{
	t_scan_state state;
	if (input_text == 39)
		state = IN_SNGL_QUOTE;
	if (input_text == 34)
		state = IN_DBL_QUOTE;
	if (input_text == 92)
		state = IN_ESCAPE;
	else
		state = IN_DEAFULT;
	return (state);
}