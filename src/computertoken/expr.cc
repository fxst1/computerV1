#include <computer.h>
#include <computertoken.h>

using namespace	fx::computer;

ComputerExpr::ComputerExpr(std::string expr):
	ComputerToken(RegexExpr, 0),
	_prefix(true),
	_factor(1, 0),
	_power(0),
	_neg(0)
{
	this->parseString( expr.c_str() );
}

ComputerExpr::ComputerExpr(const ComputerToken& m, const char *s):
	ComputerToken(m),
	_prefix(true),
	_factor(1, 0),
	_power(0),
	_neg(0)
{
	this->parseString(s);
}

ComputerToken	*ComputerExpr::nud(ComputerParserBase& parser, Computer& data)
{
	this->_prefix = false;
	return (this);
	(void)parser;
	(void)data;
}

ComputerToken	*ComputerExpr::led(ComputerParserBase& parser, ComputerToken *left, Computer& data)
{
	this->push_back(left);
	return (this);
	(void)parser;
	(void)data;
}

Value			ComputerExpr::execute(Computer& data)
{
	Value		polynome(true);
	complex_t	c = {this->_factor.getRe(), this->_factor.getIm()};

	polynome.addMember(c, this->_power);
	return (polynome);
	(void)data;
}

std::string		ComputerExpr::toString() const
{
	return ("<expr=" + this->_factor.toString(false, false) + " X ^ " + std::to_string(this->_power) + ">");
}

ComputerToken	*ComputerExpr::clone(const char *s)
{
	return (new ComputerExpr(*this, s));
}

void			ComputerExpr::parseString(const char *s)
{
	bool		factor_init = false;

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
	{
		factor_init = true;
		this->_factor.setRe(this->_neg ? -atof(s) : atof(s));
	}
	while (*s <= '9' && *s >= '0')
		s++;
	if (*s == '.')
		s++;
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

		if (!factor_init)
			this->_factor.setRe(this->_neg ? -1 : 1);

		while (isspace(*s))
			s++;

		if (*s == '^')
		{
			s++;

			while (isspace(*s))
				s++;

			this->_power = atoi(s);
		}
		else
			this->_power = 1;
	}
	else
		this->_power = 0;
}
