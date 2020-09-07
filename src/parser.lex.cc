// ./src/parser.lex.cc generated by reflex 2.1.4 from ./src/parser.ll

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


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

yy::parser::symbol_type yy::Lexer::yylex(void)
{
  static const char *REGEX_INITIAL = "(?m)(^\\h*import\\h*\".*?\")|(\\x01)|(\\x02)|(\\x05)|(\\x03)|((?:(?:\\Q//\\E)|(?:\\Q#\\E)).*)|((?:\\Q/*\\E)(?:.|\\n)*?(?:\\Q*/\\E))|((?:\\Q''\\E)(?:.|\\n)*?(?:\\Q''\\E))|([\\x09\\x0a\\x0d\\x20])|(\"(?:[^\"\\x5c]|\\\\.)*\")|((?:not)|(?:\\Q!\\E))|((?:exit))|((?:print))|((?:type))|((?:none))|((?:float))|((?:int))|((?:str))|((?:truth))|((?:list))|((?:true))|((?:false))|((?:(?:\\Q->\\E))|(?:return))|((?:(?:\\Q?\\E))|(?:if))|((?:else))|((?:while))|((?:for))|((?:and)|(?:\\Q&&\\E))|((?:or)|(?:\\Q||\\E))|((?:(?:is)[\\x20]+)|(?:\\Q==\\E))|((?:(?:is)[\\x20]+(?:not))|(?:isnt)|(?:\\Q!=\\E))|([0-9]+)|([0-9]+\\.[0-9]+)|(0(?:x|X)[0-9A-Fa-f]+)|([A-Z_a-z](?:[A-Z_a-z]|[0-9])*)|((?:\\Q<=\\E))|((?:\\Q>=\\E))|((?:\\Q**\\E))|((?:\\Q+=\\E))|((?:\\Q-=\\E))|((?:\\Q**=\\E))|((?:\\Q*=\\E))|((?:\\Q/=\\E))|((?:\\Q%=\\E))|((?:\\Q&=\\E))|((?:\\Q|=\\E))|((?:\\Q^=\\E))|((?:\\Q--\\E))|((?:\\Q++\\E))|([%&(-}])|(;+)";
  static const reflex::Pattern PATTERN_INITIAL(REGEX_INITIAL);
  if (!has_matcher())
  {
    matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
  }
  while (true)
  {
        switch (matcher().scan())
        {
          case 0:
            if (matcher().at_end())
            {
#line 62 "./src/parser.ll"
{ if (end_of_file()) return 0; }

            }
            else
            {
              throw yy::parser::syntax_error("Unknown token.");
            }
            break;
          case 1: // rule ./src/parser.ll:61: ^\h*import\h*\".*?\" :
#line 61 "./src/parser.ll"
{ LC_UPDATE; include_file(); }
            break;
          case 2: // rule ./src/parser.ll:64: \x01 :
#line 64 "./src/parser.ll"
{
	return yy::parser::make_IROOT();
}


            break;
          case 3: // rule ./src/parser.ll:69: \x02 :
#line 69 "./src/parser.ll"
{
	return yy::parser::make_ISTART();
}

            break;
          case 4: // rule ./src/parser.ll:73: \x05 :
#line 73 "./src/parser.ll"
{
	std::string input;
	std::cout << ">> ";
	std::getline(std::cin, input);
	input = "\x02" + input + "\x03\x05";
	push_matcher(new_matcher(input));
}

            break;
          case 5: // rule ./src/parser.ll:81: \x03 :
#line 81 "./src/parser.ll"
{
	return yy::parser::make_IRUN();
}


            break;
          case 6: // rule ./src/parser.ll:86: ("//"|"#").* :
#line 86 "./src/parser.ll"
// ignore comments
            break;
          case 7: // rule ./src/parser.ll:87: "/*"(.|\n)*?"*/" :
#line 87 "./src/parser.ll"
// ignore multiline comments
            break;
          case 8: // rule ./src/parser.ll:88: "''"(.|\n)*?"''" :
#line 88 "./src/parser.ll"
// ignore documentation comments
            break;
          case 9: // rule ./src/parser.ll:89: [ \t\r\n] :
#line 89 "./src/parser.ll"
// ignore whitespace



            break;
          case 10: // rule ./src/parser.ll:93: \"([^\\\"]|\\.)*\" :
#line 93 "./src/parser.ll"
{
	LC_UPDATE;
	std::string st = str();
	unsigned first = st.find('"');
	unsigned last = st.find_last_of('"');
	st = st.substr(first+1,last-first-1);
	boost::replace_all(st, "\\n", "\n");
	boost::replace_all(st, "\\r", "\r");
	boost::replace_all(st, "\\t", "\t");
	boost::replace_all(st, "\\\"", "\"");
	boost::replace_all(st, "\\'", "\'");
	return yy::parser::make_STRING(st);
}


            break;
          case 11: // rule ./src/parser.ll:108: (not)|"!" :
#line 108 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_NOT(); }

            break;
          case 12: // rule ./src/parser.ll:110: (exit) :
#line 110 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_EXIT(); }
            break;
          case 13: // rule ./src/parser.ll:111: (print) :
#line 111 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_PRINT(); }
            break;
          case 14: // rule ./src/parser.ll:112: (type) :
#line 112 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE(); }

            break;
          case 15: // rule ./src/parser.ll:114: (none) :
#line 114 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE_NONE(); }
            break;
          case 16: // rule ./src/parser.ll:115: (float) :
#line 115 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE_FLOAT(); }
            break;
          case 17: // rule ./src/parser.ll:116: (int) :
#line 116 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE_INT(); }
            break;
          case 18: // rule ./src/parser.ll:117: (str) :
#line 117 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE_STRING(); }
            break;
          case 19: // rule ./src/parser.ll:118: (truth) :
#line 118 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE_TRUTH(); }
            break;
          case 20: // rule ./src/parser.ll:119: (list) :
#line 119 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TYPE_LIST(); }
            break;
          case 21: // rule ./src/parser.ll:120: (true) :
#line 120 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_TRUE(); }
            break;
          case 22: // rule ./src/parser.ll:121: (false) :
#line 121 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_FALSE(); }

            break;
          case 23: // rule ./src/parser.ll:123: ("->")|(return) :
#line 123 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_RETURNS(); }
            break;
          case 24: // rule ./src/parser.ll:124: ("?")|(if) :
#line 124 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_IF(); }
            break;
          case 25: // rule ./src/parser.ll:125: (else) :
#line 125 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_ELSE(); }
            break;
          case 26: // rule ./src/parser.ll:126: (while) :
#line 126 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_WHILE(); }
            break;
          case 27: // rule ./src/parser.ll:127: (for) :
#line 127 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_FOR(); }
            break;
          case 28: // rule ./src/parser.ll:128: (and)|"&&" :
#line 128 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_LAND(); }
            break;
          case 29: // rule ./src/parser.ll:129: (or)|"||" :
#line 129 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_LOR(); }
            break;
          case 30: // rule ./src/parser.ll:130: ((is)[ ]+)|"==" :
#line 130 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_LEQ(); }
            break;
          case 31: // rule ./src/parser.ll:131: ((is)[ ]+(not))|(isnt)|"!=" :
#line 131 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_LNEQ();}

            break;
          case 32: // rule ./src/parser.ll:133: [0-9]+ :
#line 133 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_INT(atoi(text())); }
            break;
          case 33: // rule ./src/parser.ll:134: [0-9]+\.[0-9]+ :
#line 134 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_FLOAT(atof(text())); }
            break;
          case 34: // rule ./src/parser.ll:135: 0(x|X)[0-9a-fA-F]+ :
#line 135 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_INT(atof(text())); }

            break;
          case 35: // rule ./src/parser.ll:137: [a-zA-Z_]([a-zA-Z_]|[0-9])* :
#line 137 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_VAR(str()); }


            break;
          case 36: // rule ./src/parser.ll:140: "<=" :
#line 140 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_LTEQ(); }
            break;
          case 37: // rule ./src/parser.ll:141: ">=" :
#line 141 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_GTEQ(); }
            break;
          case 38: // rule ./src/parser.ll:142: "**" :
#line 142 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_POW(); }
            break;
          case 39: // rule ./src/parser.ll:143: "+=" :
#line 143 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_ADDEQ(); }
            break;
          case 40: // rule ./src/parser.ll:144: "-=" :
#line 144 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_SUBEQ(); }
            break;
          case 41: // rule ./src/parser.ll:145: "**=" :
#line 145 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_POWEQ(); }
            break;
          case 42: // rule ./src/parser.ll:146: "*=" :
#line 146 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_MULEQ(); }
            break;
          case 43: // rule ./src/parser.ll:147: "/=" :
#line 147 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_DIVEQ(); }
            break;
          case 44: // rule ./src/parser.ll:148: "%=" :
#line 148 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_MODEQ(); }
            break;
          case 45: // rule ./src/parser.ll:149: "&=" :
#line 149 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_BANDEQ(); }
            break;
          case 46: // rule ./src/parser.ll:150: "|=" :
#line 150 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_BOREQ(); }
            break;
          case 47: // rule ./src/parser.ll:151: "^=" :
#line 151 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_BXOREQ(); }

            break;
          case 48: // rule ./src/parser.ll:153: "--" :
#line 153 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_SUBSUB(); }
            break;
          case 49: // rule ./src/parser.ll:154: "++" :
#line 154 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::make_ADDADD(); }


            break;
          case 50: // rule ./src/parser.ll:157: [&|^><=)(*/%+-}{:,] :
#line 157 "./src/parser.ll"
{ LC_UPDATE; return yy::parser::symbol_type(chr()); }

            break;
          case 51: // rule ./src/parser.ll:159: ;+ :
#line 159 "./src/parser.ll"
{ // catches most extra ';'
	LC_UPDATE;
	return yy::parser::symbol_type(';');
}


            break;
        }
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 166 "./src/parser.ll"




