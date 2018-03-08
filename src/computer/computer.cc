#include <computer.h>

using namespace		fx::computer;

Computer::Computer():
	_polynome(std::vector<Value*>()),
	_values(std::vector<Value*>()),
	parser(ComputerParser()),
	_sign(1)
{}

Computer::~Computer()
{
	for (auto it = this->_polynome.begin();
				it != this->_polynome.end();
				it++)
		delete *it;

	for (auto it = this->_values.begin();
				it != this->_values.end();
				it++)
		delete *it;
}

Value					*Computer::allocdVar(Value *v)
{
	this->_values.push_back(v);
	return (v);
}

bool					Computer::executeCode(const std::string& s)
{
	Value				*end;

	try
	{
		if ((end = this->parser.execute(s, *this)))
		{
			write(STDOUT_FILENO, "\t", 1);
			std::cout << end->toString() << std::endl;
		}
		this->parser.debug();
	}
	catch (ComputerNoticeException& e)
	{
		return (0);
	}
	catch (ComputerException& e)
	{
		return (1);
	}
	return (1);
}

void					Computer::setMember(const Value &factor, int power)
{
	size_t				i = this->_polynome.size();
	Value				*v = nullptr;

	while (i <= (size_t)power)
	{
		this->_polynome.push_back( new Value() );
		i++;
	}

	v = this->_polynome[power];
	*v = *v + factor;
	this->_polynome[power] = v;
}

Value					*Computer::getMember(int power)
{
	return (this->_polynome[power]);
}