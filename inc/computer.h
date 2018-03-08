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
