#ifndef VALUE_H
# define VALUE_H
# include <string>

namespace	fx::computer{

	class	Value{

		double		_re;
		double		_im;

		public:

			Value(double re = 0, double im = 0):
				_re(re),
				_im(im)
			{}

			~Value(void)
			{}

			std::string	toString(void) const;

			Value		pow(const Value& v);
			Value		operator-(void);
			Value		operator+(const Value& v);
			Value		operator-(const Value& v);
			Value		operator*(const Value& v);
			Value		operator/(const Value& v);
			Value		operator%(const Value& v);
			Value		operator=(const Value& v);

			Value		*clone(void)
			{
				return (new Value(this->_re, this->_im));
			}
	};

};

#endif
