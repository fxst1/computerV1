/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:06 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 13:53:07 by fxst1            ###   ########.fr       */
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

	using ComputerParserBase = ParserBase<Value*, fx::computer::Computer&>;
	using ComputerToken = ParserTokenBase<Value*, fx::computer::Computer&>;
	using ComputerTokenInfix = ParserTokenBaseInfix<Value*, fx::computer::Computer&>;
	using ComputerTokenInfixR = ParserTokenBaseInfixR<Value*, fx::computer::Computer&>;
	using ComputerTokenPrefix = ParserTokenBasePrefix<Value*, fx::computer::Computer&>;
	using ComputerTokenTemp = ParserTokenBaseTemp<Value*, fx::computer::Computer&>;
	using ComputerException = ParserBaseException<Value*, fx::computer::Computer&>;
	using ComputerAbortException = ParserBaseAbortException<Value*, fx::computer::Computer&>;
	using ComputerNoticeException = ParserBaseNoticeException<Value*, fx::computer::Computer&>;

	class			ComputerParser: public ParserBase<Value*, fx::computer::Computer&>
	{
		public:

			ComputerParser(void);
	};

	class	Computer
	{
		std::vector<Value*>						_polynome;
		std::vector<Value*>						_values;

		public:

			ComputerParser							parser;
			int										_sign;

			Computer(void);
			~Computer(void);

			Value					*allocdVar(Value *v);
			bool					executeCode(const std::string& s);
			void					setMember(const Value &factor, int power);
			Value					*getMember(int power);
	};

};

# include <computertoken.h>

#endif
