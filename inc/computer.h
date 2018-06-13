/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:06 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/13 13:25:01 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTER_HPP
# define COMPUTER_HPP
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <map>
# include "lexerparser.h"
# include "value.h"
# include "computertoken.h"

using namespace		lexerparser;

namespace			fx::computer
{
	class			Computer;

	class			ComputerParser: public Parser<Value, Computer&>
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

#endif
