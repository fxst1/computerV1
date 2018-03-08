/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:52:03 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 13:55:28 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <value.h>

using namespace	fx::computer;

Value			Value::number_minus(void)
{
	return (Value(-this->getRe(), -this->getIm()));
}

Value			Value::number_plus(const Value& v)
{
	return (Value(this->getRe() + v.getRe(), this->getIm() - v.getIm()));
}

Value			Value::number_minus(const Value& v)
{
	return (Value(this->getRe() - v.getRe(), this->getIm() - v.getIm()));
}
