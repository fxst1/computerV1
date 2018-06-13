#ifndef LEXERTOKENSCOPE_H
# define LEXERTOKENSCOPE_H
# include "lexerparser.h"

namespace	lexerparser
{
	template<typename T, typename D>
	class		LexerTokenScope: public LexerToken<T,D>
	{
		public:

			LexerTokenScope(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerToken<T,D>				*nud(Parser<T,D>& parser, D data)
			{
				LexerToken<T,D>			*tmp = NULL;

				while (true)
				{
					tmp = parser.expression(data, this->_priority);
					if (tmp == NULL)
						break ;
					this->push_back(tmp);
				}
				return (this);
			}

			LexerToken<T,D>				*led(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
			{
				LexerToken<T,D>			*tmp = NULL;

				this->push_back(left);
				while (true)
				{
					tmp = parser.expression(data, this->_priority);
					if (tmp == NULL)
						break ;
					this->push_back(tmp);
				}
				return (this);
			}

			T							execute(D data)
			{
				T						tmp = NULL;
				T						ltmp = NULL;
				size_t					i = 0;

				while (i < this->size())
				{
					tmp = this->get(i)->execute(data);
					if (!tmp)
						break ;
					else
						ltmp = tmp;
					i++;
				}
				return (ltmp);
			}
	};
};

#endif
