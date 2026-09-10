#pragma once

#include <string>

typedef std::string string;

// Don't know why these have numbers, NVM just realized
enum class TokenType 
{
    EO_FILE = 0, // EOF is reserved
    NEWLINE = 0,
    NUMBER = 0,
    INDENT = 0,
    STRING = 0,
    LABEL = 1,
    GOTO = 1,
	PRINT = 2,
	INPUT = 104,
	LET = 105,
	IF = 106,
	THEN = 107,
	ENDIF = 108,
	WHILE = 109,
	REPEAT = 110,
	ENDWHILE = 111,
	EQ = 201,
	PLUS = 202,
	MINUS = 203,
	ASTERISK = 204,
	SLASH = 205,
	EQEQ = 206,
	NOTEQ = 207,
	LT = 208,
	LTEQ = 209,
	GT = 210,
	GTEQ = 211,
	SPACE = 999,
	ID_CHAR = 1010,
	IDENTIFIER = 1011
};

class Token 
{
    public:
        string text;
        TokenType type;

        Token(const string text, const TokenType type);
    
};