/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:52:38 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 14:38:49 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <value.h>

using namespace	fx::computer;

Value			Value::polynome_minus(void)
{
	Value					*tmp = nullptr;
	Value					p = Value(*this);
	std::vector<Value*>&	v = p.getEq();

	for (auto it = v.begin(); it != v.end(); it++)
	{
		tmp = (*it);
		*tmp = -(*tmp);
	}
	return (p);
}

Value			Value::polynome_plus(const Value& right)
{
	Value					*tmp = nullptr;
	Value					p = Value(*this);

	if (right.isPolynome())
	{
		p.resize();
		for (auto	it = p._data._eq.begin();
					it != p._data._eq.end();
					it++)
		{
			tmp = *it;
			*tmp = -(*tmp);
		}
	}
	else
	{

	}
	return (p);
}

Value			Value::polynome_minus(const Value& v)
{
	(void)v;
	return (Value());
}

void 			Value::resize(size_t n)
{
	if (this->_is_polynome)
	{
		this->_data.

	}
}
