#ifndef LEXERTOKENPREFIX_H
# define LEXERTOKENPREFIX_H
# include "lexerparser.h"

namespace	lexerparser
{
	template<typename T, typename D>
	class		LexerTokenInfixR: public LexerToken<T,D>
	{
		public:

			LexerTokenInfixR(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenInfixR(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerTokenInfixR(const LexerId& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerToken<T,D>*				led(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
			{
				this->push_back(left);
				this->push_back(parser.expression(data, this->_priority - 1));
				return (this);
			}
	};
};

#endif
