/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computer.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:10 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/06 14:52:55 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			std::vector<complex_t>	solutions;

			std::cout << "reduced form: " << end->toString() << " = 0" << std::endl;
			solutions = end->solvPolynome();
			for (auto it = solutions.begin(); it != solutions.end(); it++)
			{
				std::cout << std::to_string(*it) << std::endl;
			}
		}
		this->parser.debug();
		std::cout << "End" << std::endl;
	}
	catch (const std::regex_error& e)
	{
		std::cout << "regex_error caught: " << e.what() << '\n';
        if (e.code() == std::regex_constants::error_brack)
            std::cout << "The code was error_brack\n";
			return (0);
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
