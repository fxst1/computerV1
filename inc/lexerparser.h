#ifndef LEXERPARSER_HPP
# define LEXERPARSER_HPP
# include <iostream>
# include <string>
# include <exception>
# include <list>
# include <vector>
# include <string.h>
# include <compare.h>
# include <typeinfo>
# include <regex>

namespace		lexerparser
{
	namespace		ParserExceptionType
	{
		enum
		{
			Notice,
			Warning,
			Fatal,
			Abort
		};
	};

	class		LexerId
	{
		protected:

			const std::string	_str;
			size_t				_length;

		public:

			LexerId(void):
				_length(0)
			{}

			LexerId(const std::string &src):
				_str(src),
				_length(src.length())
			{}

			LexerId(const LexerId &src):
				_str(src._str),
				_length(src._length)
			{ *this = src; }

			LexerId				&operator=(const LexerId& rhs)
			{
				this->_length = rhs._length;
				return (*this);
			}

			virtual				~LexerId(void)
			{}

			size_t	compare(const std::string& s)
			{
				return (this->compare(s.c_str()));
			}

			size_t	compare(const char *s)
			{
				if (strncmp(s, this->_str.c_str(), this->_str.length()) == 0)
					return (this->_str.length());
				else
					return (0);
			}

			size_t	length(void) const
			{
				return (this->_str.length());
			}

			std::string	getString(void) const
			{
				return (this->_str);
			}
	};

	class		LexerIdEnclosed: public LexerId
	{
		public:

			LexerIdEnclosed(void):
				LexerId("{}")
			{}

			LexerIdEnclosed(const LexerIdEnclosed& id):
				LexerId(id)
			{}

			LexerIdEnclosed(const std::string &id):
				LexerId(id)
			{}

			virtual ~LexerIdEnclosed(void)
			{}

			size_t	compare(const std::string& s)
			{
				return (this->compare(s.c_str()));
			}

			size_t	compare(const char *s)
			{
				size_t	i = 0;
				int		open = 0;

				while (*s)
				{
					if (!strncmp(s, &this->_str.c_str()[0], 1))
						open++;
					else if (!strncmp(s, &this->_str.c_str()[1], 1))
						open--;
					else if (!open)
					{
						this->_length = i;
						return (i);
					}
					i++;
					s++;
				}
				this->_length = 0;
				return (i);
			}

			size_t	length(void) const
			{
				return (this->_length);
			}
	};

	class		LexerIdRegex: public LexerId
	{
		private:

			std::regex				_id;

		public:

			LexerIdRegex(void):
				LexerId(),
				_id()
			{}

			LexerIdRegex(const std::string &id):
				LexerId("^" + id),
				_id(std::regex(this->_str))
			{}

			LexerIdRegex(const LexerIdRegex& id):
				LexerId(id),
				_id(id._id)
			{}

			~LexerIdRegex(void)
			{}

			size_t	compare(const std::string& s)
			{
				std::smatch	pieces;

				this->_length = 0;
				if (std::regex_search(s, pieces, this->_id))
				{
					if (pieces.size() > 0)
					{
						this->_length = pieces[0].str().length();
						return (this->_length);
					}
				}
				return (this->_length);
			}

			size_t	compare(const char *s)
			{
				return (this->compare(std::string(s)));
			}

			size_t	length(void) const
			{
				return (this->_length);
			}
	};

	/*
	**	Exceptions
	*/

	class		ParserException: public std::exception
	{
		private:

			const std::string		_error;

		public:

			ParserException(void):
				_error("Undefined error")
			{}

			ParserException(const ParserException &src):
				_error(src._error)
			{}

			ParserException(const std::string &type, const std::string &error, const int line = 0):
				_error(ParserException::getError(type, error, line))
			{}

			virtual ~ParserException() throw()
			{}

			ParserException				&operator=(const ParserException &rhs)
			{
				return (*this);
				(void)rhs;
			}

			static std::string			getError(const std::string &type, const std::string &error, const int line)
			{
				std::string		ret = "";

				if (type.length() > 0)
					ret = type + ": " + error;
				else if (type.length() > 0)
					ret = error;

				if (line > 0)
					ret += ": " + std::to_string(line);

				return (ret);
			}

			virtual const char			*what() const throw()
			{
				return (this->_error.c_str());
			}
	};

	class		ParserNoticeException: public ParserException
	{
		public:

			ParserNoticeException(void):
				ParserException()
			{}

			ParserNoticeException(const ParserNoticeException &e):
				ParserException(e)
			{}

			ParserNoticeException(const std::string &error, const int line = 0):
				ParserException("Notice", error, line)
			{}

			virtual ~ParserNoticeException(void) throw()
			{}

			const char			*what() const throw()
			{
				return (ParserException::what());
			}

	};

	class		ParserWarningException: public ParserException
	{
		public:

			ParserWarningException(const std::string &error, const int line = 0):
				ParserException("Warning", error, line)
			{}

			virtual ~ParserWarningException(void) throw()
			{}

	};

	class		ParserAbortException: public ParserException
	{
		public:

			ParserAbortException(const std::string &s):
				ParserException("Abort", s)
			{
				(void)s;
			}

			ParserAbortException(const ParserAbortException &e):
				ParserException(e)
			{(void)e;}

			virtual ~ParserAbortException(void) throw()
			{}
	};


/*	class		ParserAbortException: public ParserException
	{
		public:

			ParserAbortException(void):
				ParserException()
			{}

			ParserAbortException(const ParserAbortException &e):
				ParserException(e)
			{}

			ParserAbortException(const std::string &error, const int line = 0):
				ParserException("Abort", error, line)
			{}

			virtual ~ParserAbortException(void) throw()
			{}

			const char			*what() const throw()
			{
				return (ParserException::what());
			}

	};
*/
	template<typename T, typename D>
	class		Parser;

	template<typename T, typename D>
	class		LexerToken: public std::list< LexerToken<T,D>* >
	{
		private:

			typedef std::list< LexerToken<T,D>* >	node;

		protected:

			LexerId									_id;
			int										_priority;

		public:

			int										_line;
			int										_col;

			LexerToken(void):
				node(),
				_id(),
				_priority(),
				_line(0),
				_col(0)
			{}

			LexerToken(const LexerToken& id):
				node(id),
				_id(id._id),
				_priority(id._priority),
				_line(id._line),
				_col(id._col)
			{}

			LexerToken(const LexerId& id, int priority = 0):
				node(),
				_id(id),
				_priority(priority),
				_line(0),
				_col(0)
			{}

			LexerToken(const std::string& id, int priority = 0, bool is_regex = false):
				node(),
				_id(),
				_priority(priority),
				_line(0),
				_col(0)
			{
				if (is_regex)
					this->_id = LexerIdRegex(id);
			}

			virtual ~LexerToken()
			{
				this->clear();
			}

			using node::operator=;
			typedef typename node::iterator	iterator;

			LexerToken<T,D>					helperLineNud(Parser<T,D>& parser, D data)
			{
				LexerToken<T,D>				tmp = NULL;

				while (true)
				{
					tmp = parser.expression(data, this->_priority);
					if (tmp == NULL)
						break ;
					this->push_back(tmp);
				}

				return (this);
			}

			LexerToken<T,D>*					helperLineLed(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
			{
				LexerToken<T,D>*				tmp = NULL;

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

			T						helperLineEval(D data)
			{
				T					tmp = NULL;
				T					ltmp = NULL;
				size_t				i = 0;

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

			LexerToken<T,D>*					helperNud(Parser<T,D>& parser, D data)
			{
				this->push_back(parser.expression(data, this->_priority));
				return (this);
			}

			LexerToken<T,D>*					helperLed(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
			{
				this->push_back(left);
				this->push_back(parser.expression(data, this->_priority));
				return (this);
			}

			const LexerId						&getId(void) const
			{
				return (this->_id);
			}

			bool									compare(const std::string& s)
			{
				return (this->_id.compare(s));
			}

			bool									compare(const char *s)
			{
				return (this->_id.compare(s));
			}

			size_t									length(void) const
			{
				return (this->_id.length());
			}

			int										getPriority() const
			{
				return (this->_priority);
			}

			virtual void							debug(int rec = 0) const
			{
				int									i = 0;

				while (i < rec)
				{
					std::cout << "\t";
					i++;
				}

				std::cout << this->toString() << std::endl;

				for (auto it = this->begin(); it != this->end(); it++)
					(*it)->debug(rec + 1);
			}

			virtual LexerToken<T,D>*						nud(Parser<T,D>& root, D data)
			{
				throw ParserAbortException("Syntax error: Undefined token " + this->toString());
				//return (this);
				(void)root;
				(void)data;
			}

			virtual LexerToken<T,D>*			led(Parser<T,D>& root, LexerToken<T,D>* left, D data)
			{
				throw ParserAbortException("Syntax error: Unexpected token " + this->toString());
				//return (this);
				(void)root;
				(void)left;
				(void)data;
			}

			/******/
/*
			iterator								begin()
			{
				return (node::c.begin());
			}

			iterator								end()
			{
				return (node::c.end());
			}
*/
			LexerToken<T,D>							*get(size_t index)
			{
				size_t		i = 0;

				for (auto it = this->begin(); it != this->end() ; it++)
					if (i == index)
						return (*it);
					else
						i++;
				return (NULL);
			}

			virtual T								execute(D data)
			{
				throw ParserAbortException("Parse error: Undefined execution " + this->toString());
				return (T());
				(void)data;
			}

			virtual T								execute(void)
			{
				throw ParserAbortException("Parse error: Undefined execution " + this->toString());
				return (T());
			}

			virtual LexerToken<T,D>					*clone(const char *s)
			{
				return (NULL);
				(void)s;
			}

			virtual std::string						toString() const
			{
				return (this->_id.getString());
			}

	};

	template<typename T, typename D>
	class		LexerTokenPrefix: public LexerToken<T,D>
	{
		public:

			LexerTokenPrefix(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenPrefix(const std::string& id, int priority = 0, bool is_regex = false):
				LexerToken<T,D>(id, priority, is_regex)
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

	template<typename T, typename D>
	class		LexerTokenInfix: public LexerToken<T,D>
	{
		public :

			LexerTokenInfix(const LexerToken<T,D>& id):
				LexerTokenPrefix<T,D>(id)
			{}

			LexerTokenInfix(const std::string& id, int priority = 0, bool is_regex = false):
				LexerToken<T,D>(id, priority, is_regex)
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


	template<typename T, typename D>
	class		LexerTokenInfixR: public LexerToken<T,D>
	{
		public:

			LexerTokenInfixR(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenInfixR(const std::string& id, int priority = 0, bool is_regex = false):
				LexerToken<T,D>(id, priority, is_regex)
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

	template<typename T, typename D>
	class		LexerTokenLiteral: public LexerToken<T,D>
	{
		public:

			LexerTokenLiteral(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenLiteral(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority, true)
			{}

			LexerTokenLiteral(const LexerId& id, int priority = 0):
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

	template<typename T, typename D>
	class		LexerTokenScope: public LexerToken<T,D>
	{
		public :

			LexerTokenScope(const LexerToken<T,D>& id):
				LexerToken<T,D>(id)
			{}

			LexerTokenScope(const std::string& id, int priority = 0):
				LexerToken<T,D>(id, priority, false)
			{}

			LexerTokenScope(const LexerId& id, int priority = 0):
				LexerToken<T,D>(id, priority)
			{}

			LexerToken<T,D>*				nud(Parser<T,D>& parser, D data)
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

			LexerToken<T,D>*				led(Parser<T,D>& parser, LexerToken<T,D>* left, D data)
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

			T									execute(D data)
			{
				T			tmp = NULL;
				T			ltmp = NULL;
				size_t		i = 0;

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

	template<typename T, typename D>
	class		Parser
	{
		private:


			std::vector< LexerToken<T,D>* >							_tokens;
			std::list< LexerToken<T,D>* >							_symbols;
			LexerToken<T,D>*										_root;
			typename std::vector<LexerToken<T,D>*>::iterator		_it;

		protected:

			int				_line;
			int				_col;

		public:

			typename std::vector<LexerToken<T,D>*>::iterator	iterator;

			Parser<T,D>(void):
				_tokens(),
				_symbols(),
				_root(nullptr),
				_line(0),
				_col(0)
			{}

			Parser<T,D>(const Parser<T,D>& p):
				_tokens(p._tokens),
				_symbols(p._symbols),
				_root(p._root),
				_line(p._line),
				_col(p._col)
			{}

			virtual ~Parser<T,D>(void)
			{
				for (auto it = this->_symbols.begin(); it != this->_symbols.end(); it++)
					if (*it != NULL)
						delete (*it);

				this->_symbols.clear();

				for (auto it = this->_tokens.begin(); it != this->_tokens.end(); it++)
					if (*it != NULL)
						delete (*it);
			}

			void							debug(void) const
			{
				if (this->_root)
					this->_root->debug();
			}

			virtual LexerToken<T,D>*		expression(D data, int priority = 0)
			{
				LexerToken<T,D>*			tok = NULL;
				LexerToken<T,D>*			left = NULL;

				if (this->_it == this->_tokens.end())
					return (NULL);

				tok = *(this->_it);
				this->advance();
				left = tok->nud(*this, data);

				while (left && this->_it != this->_tokens.end() &&
						priority < (*this->_it)->getPriority())
				{
					tok = *(this->_it);
					this->advance();
					left = tok->led(*this, left, data);
				}
				return (left);
			}

			bool							end()
			{
				return (this->_it == this->_tokens.end());
			}

			void							advance()
			{
				if (this->_it != this->_tokens.end())
					this->_it++;
			}

			LexerToken<T,D>*				getRoot(void) const
			{
				return (this->_root);
			}

			LexerToken<T,D>*				getToken(void)
			{
				if (this->_it != this->_tokens.end())
					return (*this->_it);
				return (nullptr);
			}

			void							find(const std::string id)
			{
				while (this->_it != this->_tokens.end() &&
						!(*this->_it)->compare(id))
					this->_it++;
			}

			void							useToken(LexerToken<T,D>* tok)
			{
				if (tok)
					this->_symbols.push_back( tok );
			}

			std::list<LexerToken<T,D>*>					copyTokens(void) const
			{
				std::list<LexerToken<T,D>*>				lst = std::list<LexerToken<T,D>*>();

				for (auto it = this->_symbols.begin(); it != this->_symbols.end(); it++)
					lst.push_back( (*it)->clone("") );
				return (lst);
			}

			void							init(const std::string s)
			{
				this->tokenize(s);
				this->_it = this->_tokens.begin();
			}

			T								execute(const std::string s, D data)
			{
				std::cout << "Tokenize" << std::endl;
				this->tokenize(s);
				this->_it = this->_tokens.begin();
				std::cout << "Expression" << std::endl;
				this->_root = this->expression(data);
				if (this->_root)
				{
					std::cout << "has root" << std::endl;
					if (this->_it != this->_tokens.end())
						throw ParserAbortException("Cannot parse `" + (*this->_it)->toString() + "`");
					return (this->_root->execute( data ));
				}
				else
					std::cout << "has not root" << std::endl;
				return (T());
			}

			void							clear(void)
			{
				this->_root = NULL;
				for (auto it = this->_tokens.begin(); it != this->_tokens.end(); it++)
					delete (*it);
				this->_tokens.clear();
			}

		private:

			void							addToken(LexerToken<T,D>* tok)
			{
				std::cout << "ADD" << std::endl;
				if (tok)
					this->_tokens.push_back( tok );
			}

			size_t							parseSymbol(const char *str)
			{
				size_t						tmp = 0;

				for (auto it = this->_symbols.begin(); it != this->_symbols.end(); it++)
				{
					tmp = (*it)->compare(str);
					if (tmp > 0)
					{
						std::string				s = std::string(str).substr(0, (*it)->length()).c_str();
						char*					stmp = (char*)s.c_str();
						LexerToken<T,D>*	tok = (*it)->clone(s.c_str());

						tok->_line = this->_line;
						tok->_col = this->_col;
						while (*stmp)
						{
							if (*stmp == '\n')
							{
								this->_line++;
								this->_col = 0;
							}
							else
								this->_col++;
							stmp++;
						}
						this->addToken(tok);
						return ((*it)->length());
					}
				}
				return (0);
			}

		protected:

			virtual void	tokenize(const char *str)
			{
				if (this->_symbols.size() == 0)
					throw ParserAbortException("No symbols");
				this->_line = 1;
				this->_col = 1;
				while (*str)
				{
					while (*str == '\n' || *str == '\t' || *str == ' ')
					{
						if (*str == '\n')
						{
							this->_line++;
							this->_col = 0;
						}
						else
							this->_col++;
						str++;
					}
					if (*str)
					{
						size_t		len = this->parseSymbol(str);

						if (!len)
						{
							std::string s = "Cannot parse `";
							s += *str;
							s += "` (";
							s += std::to_string(*str);
							s += ")";

							throw ParserAbortException(s);
						}
						else
							str += (len <= strlen(str)) ? len : strlen(str);
					}
				}
			}

			virtual void	tokenize(const std::string str)
			{
				this->tokenize(str.c_str());
			}

	};
};


#endif
