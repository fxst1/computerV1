/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:21 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 13:53:22 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>

using namespace fx::computer;

ComputerParser::ComputerParser(void):
	Parser<fx::computer::Value*, fx::computer::Computer&>()
{
	//Operators
	this->_g_symbols.push_back( new OperatorEqual() );
	this->_g_symbols.push_back( new OperatorPlus() );
	this->_g_symbols.push_back( new OperatorMinus() );

	//Initializer
	this->_g_symbols.push_back( new ComputerExpr() );
}
