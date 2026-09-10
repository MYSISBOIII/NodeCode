#include "lexer.h"



Lexer::Lexer(const string source) : source(source) 
{
    current_pos = 0;
    current_char = source.at(current_pos);
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

// ADD MORE CASES!
Token Lexer::get_token()  
{
    Token token(" ", TokenType::SPACE);

    string current_string;
    current_string.push_back(current_char);

    switch (current_char)
    {
    case '+':
        token = Token(current_string, TokenType::PLUS);
        break;
    
    case '-':
        token = Token(current_string, TokenType::PLUS);
        break;
    case '*':
        token = Token(current_string, TokenType::ASTERISK);
        break;
    case ' ':
        break;
    case '\n':
        token = Token(current_string, TokenType::NEWLINE);
        break;
    
    default:
        token = Token(current_string, TokenType::ID_CHAR);
        break;
    }

    increment_current_char();

    return token;
}

// Might be useless
char Lexer::get_next_char() 
{
    return current_pos < source.size() ? source.at(current_pos + 1) : '\0';
}

// How does this behave with newline
std::vector<Token> Lexer::get_tokenized_source(const string source) 
{
    std::vector<Token> tokens;

    for (char c : source) 
    {
        tokens.push_back(get_token());
    }

    return tokens;
}

// This definitely doesnt work right now
// Account for if identifier is only one char (a = 5)
// Maybe not good time complexity wise (with .erase)
// Iterate backwards since changing an array while iterating through it is bad
void Lexer::set_identifiers(std::vector<Token>& token_array) 
{
    for (int i = token_array.size() - 1; i >= 0; i--)
    {
        if (token_array[i].type == TokenType::ID_CHAR)
        {
            identifier.push_back(token_array[i].text[0]);
            
            if (id_start == -1) 
            {
                id_start = i;
                id_end = i;
            }

            id_end--;
        }
        else
        {
            if (identifier != "")
            {
                for (int j = id_end; j < id_start; j++)
                {
                    token_array.erase(token_array.begin() + j);
                    id_end--;
                }
                
                // Because we iterate backwards, identifier is now in reverse, so we use the string object constructor which takes two iterators
                token_array.insert(token_array.begin() + id_end, Token(string(identifier.rbegin(), identifier.rend()), TokenType::IDENTIFIER));

                id_start = -1;
                identifier = "";
            }
            else
            {
                id_start = i;
                id_end = i;

                identifier.push_back(token_array[i].text[0]);
            }
        }
    }
}