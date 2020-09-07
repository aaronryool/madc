// ./include/parser.lex.h generated by reflex 2.1.4 from ./src/parser.ll

#ifndef REFLEX___INCLUDE_PARSER_LEX_H
#define REFLEX___INCLUDE_PARSER_LEX_H
#define IN_HEADER 1
#define REFLEX_VERSION "2.1.4"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_YYLTYPE             yy::location
#define REFLEX_OPTION_YYSTYPE             yy::parser::semantic_type
#define REFLEX_OPTION_bison_cc            true
#define REFLEX_OPTION_bison_cc_namespace  yy
#define REFLEX_OPTION_bison_cc_parser     parser
#define REFLEX_OPTION_bison_complete      true
#define REFLEX_OPTION_exception           yy::parser::syntax_error("Unknown token.")
#define REFLEX_OPTION_header_file         "./include/parser.lex.h"
#define REFLEX_OPTION_lex                 yylex
#define REFLEX_OPTION_lexer               Lexer
#define REFLEX_OPTION_namespace           yy
#define REFLEX_OPTION_outfile             "./src/parser.lex.cc"
#define REFLEX_OPTION_token_eof           yy::parser::symbol_type(0)
#define REFLEX_OPTION_token_type          yy::parser::symbol_type
#define REFLEX_OPTION_yylineno            true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 1 "./src/parser.ll"

////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool@gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#include <boost/algorithm/string/replace.hpp>

#include <parser.yacc.h>
#include <config.h>



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  ABSTRACT LEXER CLASS                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/abslexer.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

namespace yy {

class Lexer : public reflex::AbstractLexer<reflex::Matcher> {
#line 26 "./src/parser.ll"

	int depth;
	void include_file()
	{
		depth++;
		if (depth > MAX_INCLUDE_DEPTH)
			exit(EXIT_FAILURE);

		std::string name;
		size_t fq = str().find('"') + 1;
		size_t sq = str().find_last_of('"');
		name = str().substr(fq, (sq - fq));

		FILE *fd = fopen(name.c_str(), "r");
		if (! fd)
			exit(EXIT_FAILURE);
		else
			push_matcher(new_matcher(fd));
	}
	bool end_of_file()
	{
		if (depth == 0)
			return true;		// return true: no more input to read
		fclose(in());			// close the file descriptor
		pop_matcher();		// delete current matcher, pop matcher
		depth--;
		return false;			// return false: continue reading
	}

 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  Lexer(
      const reflex::Input& input = reflex::Input(),
      std::ostream&        os    = std::cout)
    :
      AbstractBaseLexer(input, os)
  {
#line 55 "./src/parser.ll"

	depth = 0;

  }
  static const int INITIAL = 0;
  virtual yy::parser::symbol_type yylex(void);
};

} // namespace yy

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  BISON C++                                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#endif
