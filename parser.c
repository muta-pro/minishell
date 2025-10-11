/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:30:54 by imutavdz          #+#    #+#             */
/*   Updated: 2025/10/11 10:41:23 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
is this a VALID PIPELINE?
*/

build_ast(pipe, redirection, cmnd);

t_ast	parser(char *token)
{
	t_token	*tok;

	init_lex();
	tok = next_token();
	pars_tok(tok)
	free_tok(&tok);
	return(ast);
}
parse_pipilne();
parse_cmnd();
parse_redir();