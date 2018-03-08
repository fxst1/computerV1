/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:52:52 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/08 14:41:26 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUE_H
# define VALUE_H
# include <string>
# include <vector>
# include <string.h>

namespace	fx::computer{

	class					Value;

	typedef struct			s_number{
		double				_re;
		double				_im;
	}						t_number;

	typedef union			u_data{
		std::vector<Value*>	_eq;
		t_number			_num;
		u_data(void)
		{
			bzero(this, sizeof(u_data));
		}
		u_data(const u_data& d)
		{
			memcpy(this, &d, sizeof(u_data));
		}
		~u_data(void)
		{}
	}						t_data;

	class	Value{

		bool					_is_polynome;
		t_data					_data;

		public :

			Value(void);
			Value(bool is_polynome);
			Value(double re, double im);
			Value(std::vector<Value*> eq);
			virtual ~Value(void);

			double					getRe(void) const;
			double					getIm(void) const;
			std::vector<Value*>		getEq(void) const;


			virtual std::string		toString(void) const;
			virtual Value			*clone(void) const;
			virtual	Value			pow(const Value& v);
			virtual	Value			operator-(void);
			virtual	Value			operator+(const Value& v);
			virtual	Value			operator-(const Value& v);
			virtual	Value			operator=(const Value& v);

			Value					number_minus(void);
			Value					number_plus(const Value& v);
			Value					number_minus(const Value& v);

			Value					polynome_minus(void);
			Value					polynome_plus(const Value& v);
			Value					polynome_minus(const Value& v);

			void 					resize(size_t n);

	};

};

#endif
