#ifndef COMPUTERTOKEN_HPP
# define COMPUTERTOKEN_HPP
# include <vector>
# include <string>
# include <cstdlib>
# define RegexSign "([+-]*)"
# define RegexFactor "([0-9]+(.[0-9]+)*)"
# define RegexPower "(\\*(\\s*)X?(\\s*)^(\\s*)[0-3])"
# define RegexExpr "\\s*[+-]?\\s*(([0-9]+))?\\s*([*]?\\s*X\\s*\\^\\s*[0-2])?"

namespace		fx::computer
{
	class		Computer;

	class		ComputerExpr: public ComputerToken
	{
		Value	_factor;
		int		_power;
		int		_neg;

		public:

			ComputerExpr(std::string expr = "");
			ComputerExpr(const ComputerToken& m, const char *s);

			ComputerToken	*nud(ComputerParserBase& parser, Computer& data);
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
