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
	Value					*tmp = nullptr;
	Value					p = Value(*this);
	std::vector<Value*>		v = p.getEq();

	this->preparePolynome();
	if (this->_is_polynome)
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			tmp = p._data._eq[i];
			*tmp = -(*tmp);
		}
	return (p);
}

Value			Value::polynome_plus(const Value& right)
{
	Value					*tmp = nullptr;
	Value					p = Value(*this);

	p.preparePolynome();
	if (right.isPolynome())
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			tmp = p._data._eq[i];
			*tmp = (*tmp) + (*right._data._eq[i]);
		}
	}
	else
	{
		tmp = p._data._eq[0];
		*tmp = (*tmp) + (*right._data._eq[0]);
	}
	return (p);
}

Value			Value::polynome_minus(const Value& right)
{
	Value					*tmp = nullptr;
	Value					p = Value(*this);

	p.preparePolynome();
	if (right.isPolynome())
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			tmp = p._data._eq[i];
			*tmp = (*tmp) - (*right._data._eq[i]);
		}
	}
	else
	{
		tmp = p._data._eq[0];
		*tmp = (*tmp) - (*right._data._eq[0]);
	}
	return (p);
}

void 			Value::preparePolynome(void)
{
	Value		*tmp = nullptr;

	if (this->_is_polynome)
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			tmp = this->_data._eq[i];
			if (!tmp)
				this->_data._eq[i] = new Value(0, 0);
		}
	}
}
