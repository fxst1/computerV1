#include <computer.h>
#include <computertoken.h>

using namespace	fx::computer;

ComputerExpr::ComputerExpr(std::string expr):
	ComputerToken(RegexExpr, 0, true),
	_factor(1),
	_power(0),
	_neg(0)
{
	this->parseString( expr.c_str() );
}

ComputerExpr::ComputerExpr(const ComputerToken& m, const char *s):
	ComputerToken(m),
	_factor(((const ComputerExpr&)m)._factor),
	_power(((const ComputerExpr&)m)._power),
	_neg(((const ComputerExpr&)m)._neg)
{
	this->parseString(s);
}

ComputerToken	*ComputerExpr::nud(ComputerParserBase& parser, Computer& data)
{
	return (this);
	(void)parser;
	(void)data;
}

Value			*ComputerExpr::execute(Computer& data)
{
	data.setMember(this->_factor, this->_power);
	return (data.getMember(this->_power));
}

std::string		ComputerExpr::toString() const
{
	return ("<expr=" + this->_factor.toString() + " X ^ " + std::to_string(this->_power) + ">");
}

ComputerToken	*ComputerExpr::clone(const char *s)
{
	return (new ComputerExpr(*this, s));
}

void			ComputerExpr::parseString(const char *s)
{
	std::cout << s << std::endl;
	while (isspace(*s))
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		this->_neg = 1;
		s++;
	}

	while (isspace(*s))
		s++;

	if (*s <= '9' && *s >= '0')
		this->_factor = Value(this->_neg ? -atoi(s) : atoi(s));
	while (*s <= '9' && *s >= '0')
		s++;

	while (isspace(*s))
		s++;

	if (*s == '*')
		s++;

	while (isspace(*s))
		s++;

	if (*s == 'X')
	{
		s++;

		while (isspace(*s))
			s++;

		if (*s == '^')
			s++;

		while (isspace(*s))
			s++;

		this->_power = atoi(s);
	}
}
