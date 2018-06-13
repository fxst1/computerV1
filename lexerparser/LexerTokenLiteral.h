#ifndef LEXERTOKENPREFIX_H
# define LEXERTOKENPREFIX_H

namespace	lexerparser
{
	template<typename T, typename D>
	class		LexerTokenLiteral: public LexerToken<T,D>
	{
		public:

			LexerTokenLiteral(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerToken<T,D>*				nud(Parser<T,D>& parser, D data)
			{
				return (this);
				(void)parser;
				(void)data;
			}

			LexerToken<T,D>*				led(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
			{
				return (this);
				(void)parser;
				(void)left;
				(void)data;
			}
	};
};

#endif
