/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:17 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 16:14:25 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>
#include <computertoken.h>

using namespace		fx::computer;

OperatorMinus::OperatorMinus():
	ComputerToken("-", 140),
	_prefix(false)
{}

OperatorMinus::OperatorMinus(const ComputerToken& m, const char *s):
	ComputerToken(m),
	_prefix(false)
{(void)s;}

std::string			OperatorMinus::toString() const
{
	if (this->_prefix)
		return ("<prefix: ->");
	return ("<infix: ->");
}

ComputerToken		*OperatorMinus::nud(ComputerParserBase& parser, Computer& data)
{
	this->_prefix = true;
	return (this->helperNud(parser, data));
}

ComputerToken		*OperatorMinus::led(ComputerParserBase& parser,ComputerToken *left, Computer& data)
{
	return (this->helperLed(parser, left, data));
}

Value				*OperatorMinus::execute(Computer& data)
{
	Value			*a = this->get(0)->execute(data);
	Value			*b = nullptr;
	Value			tmp = Value();

	if (!this->_prefix)
	{
		b = this->get(1)->execute(data);
		tmp = (*a) - (*b);
		return (data.allocdVar( tmp.clone() ));
	}
	return (data.allocdVar( new Value(-(*a)) ));
}

ComputerToken*		OperatorMinus::clone(const char *s)
{
	return (new OperatorMinus(*this, s));
}
