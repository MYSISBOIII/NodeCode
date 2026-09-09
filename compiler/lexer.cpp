#include "lexer.h"

Lexer::Lexer(const string source) : source(source) 
{

}

void Lexer::increment_current_char() 
{
    current_pos++;

    if (current_pos > source.size()) 
    {
        current_char = '\0';
    } else
    {
        current_char = source.at(current_pos);
    }
}

char Lexer::get_next_char() 
{
    if (current_pos + 1 > source.size()) 
    {
        return '\0';
    }

    return source[current_pos + 1];
}

// Add more cases
Token Lexer::get_token()  
{
    Token token("", "");

    switch (current_char)
    {
    case '+':
        token = Token(current_char, TokenType::PLUS);
        break;
    
    case '-':
        token = Token(current_char, TokenType::PLUS);
        break;
    
    default:
        break;
    }

    return token;
}