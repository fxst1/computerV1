/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:13 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/06 14:52:25 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <value.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace	fx::computer;

Value::Value(void):
	_is_polynome(false)
{
	this->_num = {0, 0};
}

Value::Value(const Value &src):
	_is_polynome(src._is_polynome)
{
	*this = src;
}

Value::Value(bool is_polynome):
	_is_polynome(is_polynome)
{
	if (this->_is_polynome)
		bzero(this->_eq, sizeof(this->_eq));
	else
		this->_num = {0, 0};
}

Value::Value(number_t re, number_t im):
	_is_polynome(false),
	_num({re, im})
{}

Value::Value(const complex_t &num):
	_is_polynome(true),
	_num(num)
{}

Value::Value(complex_t *eq):
	_is_polynome(true)
{
	memcpy(this->_eq, eq, sizeof(this->_eq));
}

Value::~Value(void)
{}

static std::string			getPrecisionString(double v)
{
	int				i;
	int				j;
	std::string		ret;
	std::string		s = std::to_string(v);

	i = s.length() - 1;
	while (s[i] == '0' && i >= 0)
		i--;

	if (s[i] == '.')
		i--;

	j = 0;
	while (s[j] && j <= i)
		ret += s[j++];

	return (ret);
}

static std::string	abs2str(const double v, bool addsign, bool space)
{
	std::stringstream	ss;

	if (std::isnan(v))
		ss << "nan";
	else
	{
		if (v < 0)
		{
			if (space)
				ss << "- " << getPrecisionString(-v);
			else
				ss << "-" << getPrecisionString(-v);
		}
		else
		{
			if (addsign)
			{
				if (space)
					ss << "+ " << getPrecisionString(v);
				else
					ss << "+" << getPrecisionString(v);
			}
			else
				ss << getPrecisionString(v);
		}
	}
	return (ss.str());
}

std::string			std::to_string(const complex_t &c, bool addsign, bool space)
{
	if (c._im)
		return (abs2str(c._re, addsign, space) + abs2str(c._im, addsign, space));
	return (abs2str(c._re, addsign, space));
}

std::string			Value::toString(bool addsign, bool space) const{

	std::string			s = "";

	if (this->isNumber())
		return (std::to_string(this->_num, addsign, space));
	else
	{
		for (size_t i = 0; i < MAX_DEGREE; i++)
		{
			if (i > 0)
				s += " ";

			s += std::to_string(this->_eq[i], addsign, space);
			s += " * X^" + std::to_string(i);
			addsign = true;
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

Value		&Value::operator=(const Value& v){

	if (this != &v)
	{
		this->_is_polynome = v._is_polynome;
		if (this->_is_polynome)
			memcpy(this->_eq, v._eq, sizeof(this->_eq));
		else
			this->_num = v._num;
	}
	return (*this);
}

Value		*Value::clone(void) const {
	if (this->_is_polynome)
		return (new Value(this->getEq()));
	return (new Value(this->getRe(), this->getIm()));
}

number_t		Value::getRe(void) const {
	return (this->_num._re);
}

number_t		Value::getIm(void) const {
	return (this->_num._im);
}

complex_t	*Value::getEq(void) const {
	return ((complex_t*)this->_eq);
}

void		Value::setRe(number_t re){
	this->_num._re = re;
}

void		Value::setIm(number_t im){
	this->_num._im = im;
}
void		Value::setEq(complex_t *eq){
	memcpy(this->_eq, eq, sizeof(this->_eq));
}

void		Value::addMember(complex_t &v, int power){
	if (this->_is_polynome)
		this->_eq[power] = v;
}

bool		Value::isPolynome(void) const {
	return (this->_is_polynome == true);
}

bool		Value::isNumber(void) const {
	return (this->_is_polynome == false);
}

void		Value::solvDeg2(std::vector<complex_t> &solutions) const
{
	double		a = this->_eq[2]._re,
				b = this->_eq[1]._re,
				c = this->_eq[0]._re,
				delta = (b * b) - (4 * a * c);

	std::cout << "Polynomial degree: 2" << std::endl;
	if (delta > 0)
	{
		complex_t	s1 = {(-b + std::sqrt(delta)) / (2 * a), 0};
		complex_t	s2 = {(-b - std::sqrt(delta)) / (2 * a), 0};

		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		solutions.push_back(s1);
		solutions.push_back(s2);
	}
	else if (delta == 0)
	{
		complex_t	s = {-(b / (2 * a)), 0};

		std::cout << "Discriminant is nul, the solution is:" << std::endl;
		solutions.push_back(s);
	}
	else
	{
		complex_t	s1 = {-b / (2 * a), std::sqrt(delta) / (2 * a)};
		complex_t	s2 = {-b / (2 * a), -std::sqrt(delta) / (2 * a)};

		std::cout << "Discriminant is strictly negative, the two solutions complex are:" << std::endl;
		solutions.push_back(s1);
		solutions.push_back(s2);
	}
}

void		Value::solvDeg1(std::vector<complex_t> &solutions) const
{
	double		a = this->_eq[1]._re,
				b = this->_eq[0]._re;

	std::cout << "Polynomial degree: 1" << std::endl;
	solutions.push_back({-b / a, 0});
}

void		Value::solvDeg0(std::vector<complex_t> &solutions) const
{
//	double		a = this->_eq[0]._re;

	std::cout << "Polynomial degree: 0" << std::endl;
	std::cout << "This expression has no sense" << std::endl;
/*	if (a != 0)
	{
		solutions.push_back({NAN, 0});
	}
	else
		solutions.push_back({a, 0});*/
	(void)solutions;
}

std::vector<complex_t>		Value::solvPolynome(void) const {

	std::vector<complex_t>	solutions;

	if (this->_eq[2]._re != 0)
		this->solvDeg2(solutions);
	else if (this->_eq[1]._re != 0)
		this->solvDeg1(solutions);
	else
		this->solvDeg0(solutions);
	return (solutions);
}

std::ostream					&operator<<(std::ostream &o, const Value& v)
{
	o << v.toString();
	return (o);
}
