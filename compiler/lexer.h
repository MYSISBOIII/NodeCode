#pragma once

#include <string>

#include <cstdint>

typedef std::string string;

class Lexer
{
    public:

    string source;
    char current_char;
    uint16_t current_pos;

    Lexer(const string source);
    
    void increment_current_char();
    char get_next_char();
};