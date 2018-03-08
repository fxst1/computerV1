/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:13 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 11:45:44 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <value.h>

using namespace	fx::computer;

std::string	Value::toString(void) const{

	if (this->_im)
	{
		if (this->_im > 0)
			return (std::to_string(this->_re) + " + " + std::to_string(this->_im) + "i");
		return (std::to_string(this->_re) + " - " + std::to_string(-this->_im) + "i");
	}
	return (std::to_string(this->_re));
}

Value		Value::pow(const Value& v){

	return (Value(this->_re, this->_im));
	(void)v;
}

Value		Value::operator-(void){

	return (Value(-this->_re, -this->_im));
}

Value		Value::operator+(const Value& v){

	return (Value(this->_re + v._re, this->_im + v._im));
}

Value		Value::operator-(const Value& v){

	return (Value(this->_re - v._re, this->_im - v._im));
}

Value		Value::operator*(const Value& v){

	return (Value(this->_re * v._re, this->_im * v._im));
}

Value		Value::operator/(const Value& v){

	return (Value((int)this->_re / (int)v._re, (int)this->_im / (int)v._im));
}

Value		Value::operator%(const Value& v){

	return (Value((int)this->_re % (int)v._re, (int)this->_im % (int)v._im));
}

Value		Value::operator=(const Value& v){

	this->_re = v._re;
	this->_im = v._im;
	return (*this);
}
