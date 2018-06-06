/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computertoken.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:52:59 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/06 13:19:14 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTERTOKEN_HPP
# define COMPUTERTOKEN_HPP
# include <vector>
# include <string>
# include <cstdlib>
//# define RegexExpr "\\s*([+-]?\\s*[0-9]+)?\\s*([*]?\\s*X\\s*(\\^\\s*[0-2])?)?"
# define RegexExpr "\\s*(([+-]?\\s*[0-9]+)|([+-])?)?\\s*([*]?\\s*X\\s*(\\^\\s*[0-2])?)?"

namespace		fx::computer
{
	class		Computer;

	class		ComputerExpr: public ComputerToken
	{
		bool	_prefix;
		Value	_factor;
		int		_power;
		int		_neg;

		public:

			ComputerExpr(std::string expr = "");
			ComputerExpr(const ComputerToken& m, const char *s);

			ComputerToken	*nud(ComputerParserBase& parser, Computer& data);
			ComputerToken	*led(ComputerParserBase& parser, ComputerToken *left, Computer& data);
			Value			*execute(Computer& data);
			std::string		toString() const;
			ComputerToken	*clone(const char *s);
			void 			parseString(const char *s);
	};

	class		OperatorEqual: public ComputerTokenInfix
	{
		public:

			OperatorEqual(void);
			OperatorEqual(const ComputerTokenInfix& m, const char *s);

			std::string			toString() const;
			Value				*execute(Computer& data);
 			ComputerToken*		clone(const char *s);
 	};

	class		OperatorMinus: public ComputerToken
	{
		bool	_prefix;

		public:

			OperatorMinus(void);
			OperatorMinus(const ComputerToken& m, const char *s);

			std::string			toString() const;
			ComputerToken		*nud(ComputerParserBase& parser, Computer& data);
			ComputerToken		*led(ComputerParserBase& parser, ComputerToken *left, Computer& data);
			Value				*execute(Computer& data);
 			ComputerToken*		clone(const char *s);
 	};

	class		OperatorPlus: public ComputerToken
	{
		bool	_prefix;

		public:

			OperatorPlus(void);
			OperatorPlus(const ComputerToken& m, const char *s);

			std::string			toString() const;
			ComputerToken		*nud(ComputerParserBase& parser, Computer& data);
			ComputerToken		*led(ComputerParserBase& parser, ComputerToken *left, Computer& data);
			Value				*execute(Computer& data);
 			ComputerToken*		clone(const char *s);
 	};

};

#endif
