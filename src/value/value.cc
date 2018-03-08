/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:13 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 17:04:17 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <value.h>
#include <iostream>

using namespace	fx::computer;

Value::Value(void):
	_is_polynome(false)
{
	bzero(&this->_data, sizeof(this->_data));
	std::cout << "DEF" << std::endl;
}

Value::Value(bool is_polynome):
	_is_polynome(is_polynome)
{
	bzero(&this->_data, sizeof(this->_data));
	std::cout << "BOOL" << std::endl;
}

Value::Value(double re, double im):
	_is_polynome(false)
{
	bzero(&this->_data, sizeof(this->_data));
	this->_data._num._re = re;
	this->_data._num._re = im;
	std::cout << "NUMBER" << std::endl;
}

Value::Value(std::vector<Value*> eq):
	_is_polynome(true)
{
	bzero(&this->_data, sizeof(this->_data));
	this->_data._eq = std::vector<Value*>();

	for (auto it = eq.begin(); it != eq.end(); it++)
		this->_data._eq.push_back( (*it)->clone() );
	std::cout << "POLYNOME" << std::endl;
}

Value::~Value(void)
{
	if (this->_is_polynome)
		for (auto	it = this->_data._eq.begin();
					it != this->_data._eq.end();
					it++)
			delete (*it);
	bzero(&this->_data, sizeof(this->_data));
}

std::string	Value::toString(void) const{

	std::string			s = "";

	if (this->isNumber())
	{
		if (this->getIm())
		{
			if (this->getIm() > 0)
				return (std::to_string(this->getRe()) + " + " + std::to_string(this->getIm()) + "i");
			return (std::to_string(this->getRe()) + " - " + std::to_string(-this->getIm()) + "i");
		}
		return (std::to_string(this->getRe()));
	}
	else
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			if (i > 0)
				s += " ";
			if (i < this->_data._eq.size())
				s += this->_data._eq[i]->toString();
			else
				s += "0";
			if (i > 0)
				s += " X^" + std::to_string(i);
		}
	}
	return (s);
}

Value		Value::pow(const Value& v){

	return (Value(this->getRe(), this->getIm()));
	(void)v;
}

Value		Value::operator-(void){

	if (this->_is_polynome)
		return (polynome_minus());
	return (number_minus());
}

Value		Value::operator+(const Value& v){

	if (this->_is_polynome)
		return (polynome_plus(v));
	return (number_plus(v));
}

Value		Value::operator-(const Value& v){

	if (this->_is_polynome)
		return (polynome_minus(v));
	return (number_minus(v));
}

Value		Value::operator=(const Value& v){

	this->_is_polynome = v._is_polynome;
	memcpy(&this->_data, &v._data, sizeof(v._data));
	return (*this);
}

Value		*Value::clone(void) const {
	if (this->_is_polynome)
		return (new Value(this->getEq()));
	return (new Value(this->getRe(), this->getIm()));
}

double		Value::getRe(void) const {
	return (this->_data._num._re);
}

double		Value::getIm(void) const {
	return (this->_data._num._im);
}

std::vector<Value*>		Value::getEq(void) const {
	return (this->_data._eq);
}

void		Value::setRe(double re){
	this->_data._num._re = re;
}

void		Value::setIm(double im){
	this->_data._num._im = im;
}
void		Value::setEq(std::vector<Value*> eq){
	this->_data._eq = eq;
}

bool		Value::isPolynome(void) const {
	return (this->_is_polynome == true);
}

bool		Value::isNumber(void) const {
	return (this->_is_polynome == false);
}
