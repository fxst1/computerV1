#ifndef COMPUTERDEF_H
# define COMPUTERDEF_H
# include "value.h"
# include "lexerparser.h"

using namespace lexerparser;

namespace		fx::computer
{
	class			Computer;

	using			ComputerParserBase = Parser<Value, Computer&>;
	using			ComputerToken = LexerToken<Value, Computer&>;
	using			ComputerTokenInfix = LexerTokenInfix<Value, Computer&>;
	using			ComputerException = ParserException;
	using			ComputerAbortException = ParserAbortException;
	using			ComputerNoticeException = ParserNoticeException;
};

#endif
