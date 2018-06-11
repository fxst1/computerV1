/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:52:52 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/06 14:10:23 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUE_H
# define VALUE_H
# include <iostream>
# include <string>
# include <vector>
# include <string.h>
# include <cmath>
# include <cfloat>
# include <limits>
# define	MAX_DEGREE 3
namespace	fx::computer{

	typedef struct				complex
	{
		double					_re;
		double					_im;
	}							complex_t;

	class							Value
	{

		bool					_is_polynome;

		union
		{
			complex_t				_eq[MAX_DEGREE];
			complex_t				_num;
		};

		public:

			Value(void);					//Default
			Value(const Value &src);		//Copy
			Value(bool is_polynome);		//Empty
			Value(double re, double im);	//Complex 1
			Value(const complex_t &num);	//Complex 2
			Value(complex_t *eq);			//Polynome
			virtual ~Value(void);

			double					getRe(void) const;
			double					getIm(void) const;
			complex_t				*getEq(void) const;

			void					setRe(double re);
			void					setIm(double im);
			void					setEq(complex_t* eq);
			void					addMember(complex_t &v, int power);

			bool					isPolynome(void) const;
			bool					isNumber(void) const;

			virtual std::string		toString(void) const;
			virtual Value			*clone(void) const;
			virtual	Value			pow(const Value& v);
			virtual	Value			operator-(void);
			virtual	Value			operator+(const Value& v);
			virtual	Value			operator-(const Value& v);
			virtual	Value			&operator=(const Value& v);

			Value					number_minus(void);
			Value					number_plus(const Value& v);
			Value					number_minus(const Value& v);

			Value					polynome_minus(void);
			Value					polynome_plus(const Value& v);
			Value					polynome_minus(const Value& v);

			void					solvDeg2(std::vector<complex_t> &solutions) const;
			void					solvDeg1(std::vector<complex_t> &solutions) const;
			void					solvDeg0(std::vector<complex_t> &solutions) const;
			std::vector<complex_t>	solvPolynome(void) const;
	};

};

namespace std
{
	string						to_string(const fx::computer::complex_t &c);
};

std::ostream					&operator<<(std::ostream &o, const fx::computer::Value& v);

#endif
