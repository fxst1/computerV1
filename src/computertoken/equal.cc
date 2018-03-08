#include <computer.h>
#include <computertoken.h>

using namespace		fx::computer;

OperatorEqual::OperatorEqual():
	ParserTokenInfix<Value*, Computer&>("=", 80)
{}

OperatorEqual::OperatorEqual(const ComputerTokenInfix& m, const char *s):
	ComputerTokenInfix(m)
{(void)s;}

std::string			OperatorEqual::toString() const
{
	return ("<=>");
}

Value				*OperatorEqual::execute(Computer& data)
{
	Value			*a = this->get(0)->execute(data);

	data._sign = -1;
	return (a);
}

ComputerToken*		OperatorEqual::clone(const char *s)
{
	return (new OperatorEqual(*this, s));
}
