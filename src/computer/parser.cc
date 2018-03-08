#include <computer.h>

using namespace fx::computer;

ComputerParser::ComputerParser(void):
	Parser<fx::computer::Value*, fx::computer::Computer&>()
{
	//Operators
	this->_g_symbols.push_back( new OperatorEqual() );

	//Initializer
	this->_g_symbols.push_back( new ComputerExpr() );
}
