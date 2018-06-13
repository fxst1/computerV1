/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computer.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:10 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/13 21:13:50 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>

using namespace		fx::computer;
using namespace		lexerparser;

Computer::Computer():
	_values(),
	_parser(ComputerParser()),
	_sign(1)
{}

Computer::~Computer()
{}

Value					&Computer::allocdVar(Value &v)
{
	this->_values.push_back(v);
	return (v);
}

bool					Computer::executeCode(const std::string& s)
{
	Value				end;

	try
	{
		end = this->_parser.evaluate(s, *this);
		if (this->_parser.ok())
		{
			std::vector<complex_t>	solutions;

			std::cout << "Reduced form: " << end.toString(false, true) << " = 0" << std::endl;
			solutions = end.solvPolynome();
			for (auto it = solutions.begin(); it != solutions.end(); it++)
			{
				std::cout << std::to_string(*it, false, false) << std::endl;
			}
		}
		else
			std::cout << "?" << std::endl;
	}
	catch (const std::regex_error& e)
	{
		std::cout << "regex_error caught: " << e.what() << '\n';
        if (e.code() == std::regex_constants::error_brack)
            std::cout << "The code was error_brack\n";
			return (0);
	}
	catch (const ParserNoticeException& e1)
	{
		std::cout << e1.what() << std::endl;
		return (0);
	}
	catch (const ParserAbortException& e2)
	{
		std::cout << e2.what() << std::endl;
		return (1);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (1);
}
