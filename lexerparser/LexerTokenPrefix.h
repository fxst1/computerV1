#ifndef LEXERTOKENPREFIX_H
# define LEXERTOKENPREFIX_H

namespace	lexerparser
{
	template<typename T, typename D>
	class		LexerTokenPrefix: public LexerToken<T,D>
	{
		public:

			LexerTokenPrefix(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenPrefix(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerTokenPrefix(const LexerId& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			virtual ~LexerTokenPrefix(void)
			{}

			virtual LexerToken<T,D>*				nud(Parser<T,D>& parser, D data)
			{
				this->push_back(parser.expression(data, this->_priority));
				return (this);
			}

	};
};

#endif
