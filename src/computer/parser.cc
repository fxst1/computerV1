/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:21 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 17:05:37 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>
#include <regex>

using namespace fx::computer;

ComputerParser::ComputerParser(void):
	Parser<fx::computer::Value*, fx::computer::Computer&>()
{
	try
	{
		//Initializer
		this->_g_symbols.push_back( new ComputerExpr() );

		//Operators
		this->_g_symbols.push_back( new OperatorEqual() );
		//this->_g_symbols.push_back( new OperatorPlus() );
		//this->_g_symbols.push_back( new OperatorMinus() );

	}
	catch (const std::regex_error& e){
		std::cout << "regex_error caught: " << e.what() << '\n';
		std::cout << "code: " << std::to_string(e.code()) << '\n';
		if (e.code() == std::regex_constants::error_brack) {
			std::cout << "The code was error_brack\n";
		}
	}
}
