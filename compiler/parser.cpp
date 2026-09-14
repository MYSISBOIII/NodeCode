#include "parser.h"

Parser::Parser()
{

}

// maybe use constexpr?

/*
template <typename T>
bool Parser::is_literal(T var)
{
    return (std::is_integral_v<T> || std::is_same_v<T>);
}
*/

template <typename T>
std::vector<T> Parser::produce_AST(string source)
{
    Lexer lexer(source);
    std::vector<Token> tokenized_source = lexer.get_tokenized_source(source);
    
    lexer.set_identifiers(tokenized_source);

    for (int i = 0; i < tokenized_source.size(); i++)
    {
        
    }
}