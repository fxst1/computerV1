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
	Value			*a = nullptr;
	Value			*b = nullptr;this->get(0)->execute(data);
	Value			tmp;

	a = this->get(0)->execute(data);
	b = this->get(1)->execute(data);
	tmp = (*a) - (*b);
	return (data.allocdVar( tmp.clone() ));
}

ComputerToken*		OperatorEqual::clone(const char *s)
{
	return (new OperatorEqual(*this, s));
}
