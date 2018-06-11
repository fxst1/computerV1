/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:52:38 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 16:44:34 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <value.h>

using namespace	fx::computer;

Value			Value::polynome_minus(void)
{
	Value					p(*this);

	for (size_t i = 0; i < MAX_DEGREE; i++)
		p._eq[i] = {-p._eq[i]._re, -p._eq[i]._im};
	return (p);
}

Value			Value::polynome_plus(const Value& right)
{
	Value					p = Value(*this);

	if (right.isPolynome())
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			complex_t 	&tmp = p._eq[i];
			p._eq[i] = {tmp._re + right._eq[i]._re, tmp._im + right._eq[i]._im};
		}
	}
	else
	{
		complex_t 	&tmp = p._eq[0];
		p._eq[0] = {tmp._re + right._num._re, tmp._im + right._num._im};
	}
	return (p);
}

Value			Value::polynome_minus(const Value& right)
{
	Value					p = Value(*this);

	if (right.isPolynome())
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			complex_t 	&tmp = p._eq[i];
			p._eq[i] = {tmp._re - right._eq[i]._re, tmp._im - right._eq[i]._im};

		}
	}
	else
	{
		complex_t 	&tmp = p._eq[0];
		p._eq[0] = {tmp._re - right._num._re, tmp._im - right._num._im};
	}
	return (p);
}
