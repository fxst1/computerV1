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
	_values(),
	parser(ComputerParser()),
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
		end = this->parser.execute(s, *this);
		if (this->parser.ok())
		{
			std::vector<complex_t>	solutions;

			std::cout << "Reduced form: " << end.toString(false, true) << " = 0" << std::endl;
			solutions = end.solvPolynome();
			for (auto it = solutions.begin(); it != solutions.end(); it++)
			{
				std::cout << std::to_string(*it, false, false) << std::endl;
			}
		}
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
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (1);
}
