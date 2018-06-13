#include <computer.h>
#include <computertoken.h>

using namespace		fx::computer;

OperatorEqual::OperatorEqual():
	ComputerTokenInfix("^=", 80)
{}

OperatorEqual::OperatorEqual(const ComputerTokenInfix& m, const char *s):
	ComputerTokenInfix(m)
{(void)s;}

std::string			OperatorEqual::toString() const
{
	return ("<=>");
}

Value				OperatorEqual::execute(Computer& data)
{
	Value			a;
	Value			b;
	Value			tmp;


	if (!this->get(0))
		throw ComputerAbortException("Missing operand before `=`");
	else if (!this->get(1))
		throw ComputerAbortException("Missing operand after `=`");

	if (data._sign != 1)
		throw ComputerAbortException("Cannot use multiple times `=` token");

	data._sign--;

	a = this->get(0)->execute(data);
	b = this->get(1)->execute(data);

	tmp = a - b;
	return (tmp);
}

ComputerToken*		OperatorEqual::clone(const char *s)
{
	return (new OperatorEqual(*this, s));
}
