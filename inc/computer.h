/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:06 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/06 13:31:47 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTER_HPP
# define COMPUTER_HPP
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <parser.h>
# include <map>
# include <value.h>

namespace						fx::computer
{
	class						Computer;

	using ComputerParserBase = ParserBase<Value, Computer&>;
	using ComputerToken = ParserTokenBase<Value, Computer&>;
	using ComputerTokenInfix = ParserTokenBaseInfix<Value, Computer&>;
	using ComputerTokenInfixR = ParserTokenBaseInfixR<Value, Computer&>;
	using ComputerTokenPrefix = ParserTokenBasePrefix<Value, Computer&>;
	using ComputerTokenTemp = ParserTokenBaseTemp<Value, Computer&>;
	using ComputerException = ParserBaseException<Value, Computer&>;
	using ComputerAbortException = ParserBaseAbortException<Value, Computer&>;
	using ComputerNoticeException = ParserBaseNoticeException<Value, Computer&>;

	class			ComputerParser: public ParserBase<Value, Computer&>
	{
		public:

			ComputerParser(void);
			bool			ok(void);
	};

	class	Computer
	{
		std::vector<Value>						_values;

		public:

			ComputerParser							parser;
			int										_sign;

			Computer(void);
			~Computer(void);

			Value					&allocdVar(Value &v);
			bool					executeCode(const std::string& s);
	};

};

# include <computertoken.h>

#endif
