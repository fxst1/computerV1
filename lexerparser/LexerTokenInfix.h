#ifndef LEXERTOKENINFIX_H
# define LEXERTOKENINFIX_H
# include "lexerparser.h"

namespace	lexerparser
{
	template<typename T, typename D>
	class		LexerTokenInfix: public LexerToken<T,D>
	{
		public:

			LexerTokenInfix(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenInfix(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerTokenInfix(const LexerId& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerToken<T,D>*				led(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
			{
				this->push_back(left);
				this->push_back(parser.expression(data, this->_priority));
				return (this);
			}
	};
};

#endif
