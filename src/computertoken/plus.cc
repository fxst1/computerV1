/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:13 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 14:09:39 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>
#include <computertoken.h>

using namespace		fx::computer;

OperatorPlus::OperatorPlus():
	ComputerToken("+", 140, true),
	_prefix(false)
{}

OperatorPlus::OperatorPlus(const ComputerToken& m, const char *s):
	ComputerToken(m),
	_prefix(false)
{(void)s;}

std::string			OperatorPlus::toString() const
{
	if (this->_prefix)
		return ("<prefix: ->");
	return ("<infix: ->");
}

ComputerToken		*OperatorPlus::nud(ComputerParserBase& parser, Computer& data)
{
	this->_prefix = true;
	return (this->helperNud(parser, data));
}

ComputerToken		*OperatorPlus::led(ComputerParserBase& parser,ComputerToken *left, Computer& data)
{
	return (this->helperLed(parser, left, data));
}

Value				*OperatorPlus::execute(Computer& data)
{
	Value			*a = this->get(0)->execute(data);
	Value			*b = nullptr;
	Value			tmp = Value();

	if (this->_prefix)
	{
		b = this->get(1)->execute(data);
		tmp = (*a) + (*b);
		return (data.allocdVar( tmp.clone() ));
	}
	return (data.allocdVar( a->clone() ));
}

ComputerToken*		OperatorPlus::clone(const char *s)
{
	return (new OperatorPlus(*this, s));
}
