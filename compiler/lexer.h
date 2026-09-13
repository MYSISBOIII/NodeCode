#pragma once

#include <string>
#include <cstdint>
#include <vector>

#include <type_traits>

#include "token.h"

typedef std::string string;

class Lexer
{
    public:

        string source;
        char current_char;
        uint16_t current_pos;

        string identifier = "";

        // Might consider making these bigger
        uint16_t id_start = -1;
        uint16_t id_end;

        Lexer(const string source);
        
        // Used in get_token
        void increment_current_char();

        Token get_token();
        std::vector<Token> get_tokenized_source(const string source);
        char get_next_char();
        void set_identifiers(std::vector<Token>& token_array);
};