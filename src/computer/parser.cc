/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:21 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/13 17:32:23 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>
#include <regex>

using namespace fx::computer;

ComputerParser::ComputerParser(void):
	Parser<fx::computer::Value, fx::computer::Computer&>(),
	_expr(),
	_minus(),
	_plus(),
	_equal()
{
	try
	{
		//Operators
		this->useToken( this->_equal );
		this->useToken( this->_plus );
		this->useToken( this->_minus );

		//Initializer
		this->useToken( this->_expr );
	}
	catch (const std::regex_error& e){
		std::cout << "regex_error caught: " << e.what() << '\n';
		std::cout << "code: " << std::to_string(e.code()) << '\n';
		if (e.code() == std::regex_constants::error_brack) {
			std::cout << "The code was error_brack\n";
		}
	}
}

bool		ComputerParser::ok(void)
{
	return (this->getRoot() != nullptr);
}
